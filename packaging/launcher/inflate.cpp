// Hexic HD PC - launcher: a small zlib/DEFLATE decoder.
//
// Needed for one job: the game's HexicDeluxe.swf is stored compressed ("CWS"),
// and the High Scores patch (patch.cpp) edits the decompressed movie. Written
// from the DEFLATE format (RFC 1951) and the zlib wrapper (RFC 1950), in the
// shape of Mark Adler's public reference decoder "puff" (zlib licence): a
// bit-at-a-time canonical Huffman decoder, which is plenty fast for one
// few-megabyte file and easy to check by eye.
#include "launcher.h"

#include <cstring>

namespace hexic {
namespace {

constexpr int kMaxBits = 15;
constexpr int kLitLenCodes = 288;
constexpr int kDistCodes = 30;
// A compressed SWF is a few megabytes; a bound keeps a damaged or hostile
// file from asking for gigabytes.
constexpr size_t kMaxOutput = size_t(256) << 20;

struct Huffman {
  uint16_t count[kMaxBits + 1] = {};  // number of codes of each length
  uint16_t symbol[kLitLenCodes] = {};  // symbols ordered by code
};

class Decoder {
 public:
  Decoder(const uint8_t* data, size_t size, std::vector<uint8_t>* out) : in_(data), size_(size), out_(out) {}

  bool Run() {
    for (bool last = false; !last;) {
      uint32_t header = 0;
      if (!Bits(3, &header)) return false;
      last = (header & 1) != 0;
      bool ok = false;
      switch (header >> 1) {
        case 0: ok = Stored(); break;
        case 1: ok = Fixed(); break;
        case 2: ok = Dynamic(); break;
        default: ok = false;  // reserved block type
      }
      if (!ok) return false;
    }
    return true;
  }

  size_t consumed() const { return pos_; }

 private:
  bool Bits(int need, uint32_t* value) {
    uint32_t v = bitbuf_;
    while (bitcnt_ < need) {
      if (pos_ >= size_) return false;
      v |= uint32_t(in_[pos_++]) << bitcnt_;
      bitcnt_ += 8;
    }
    bitbuf_ = v >> need;
    bitcnt_ -= need;
    *value = v & ((1u << need) - 1);
    return true;
  }

  // Decodes one symbol; -1 on running out of input, -2 on an invalid code.
  int Decode(const Huffman& h) {
    int code = 0, first = 0, index = 0;
    for (int len = 1; len <= kMaxBits; ++len) {
      uint32_t bit = 0;
      if (!Bits(1, &bit)) return -1;
      code |= static_cast<int>(bit);
      const int count = h.count[len];
      if (code - count < first) return h.symbol[index + (code - first)];
      index += count;
      first += count;
      first <<= 1;
      code <<= 1;
    }
    return -2;
  }

  // Builds the decoding tables from code lengths. Returns 0 for a complete
  // code, > 0 for an incomplete one, < 0 for an over-subscribed one.
  static int Construct(Huffman* h, const uint16_t* length, int n) {
    for (int len = 0; len <= kMaxBits; ++len) h->count[len] = 0;
    for (int s = 0; s < n; ++s) ++h->count[length[s]];
    if (h->count[0] == n) return 0;  // no codes: complete, but nothing to decode
    int left = 1;
    for (int len = 1; len <= kMaxBits; ++len) {
      left <<= 1;
      left -= h->count[len];
      if (left < 0) return left;
    }
    uint16_t offsets[kMaxBits + 1];
    offsets[1] = 0;
    for (int len = 1; len < kMaxBits; ++len) offsets[len + 1] = offsets[len] + h->count[len];
    for (int s = 0; s < n; ++s) {
      if (length[s] != 0) h->symbol[offsets[length[s]]++] = static_cast<uint16_t>(s);
    }
    return left;
  }

  bool Codes(const Huffman& lencode, const Huffman& distcode) {
    static const uint16_t kLens[29] = {3,  4,  5,  6,  7,  8,  9,  10, 11,  13,  15,  17,  19,  23, 27,
                                       31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258};
    static const uint16_t kLenExtra[29] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2,
                                           2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0};
    static const uint16_t kDists[30] = {1,   2,   3,   4,   5,   7,    9,    13,   17,   25,
                                        33,  49,  65,  97,  129, 193,  257,  385,  513,  769,
                                        1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577};
    static const uint16_t kDistExtra[30] = {0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6,
                                            6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13};
    for (;;) {
      int symbol = Decode(lencode);
      if (symbol < 0) return false;
      if (symbol < 256) {
        if (out_->size() >= kMaxOutput) return false;
        out_->push_back(static_cast<uint8_t>(symbol));
      } else if (symbol == 256) {
        return true;
      } else {
        symbol -= 257;
        if (symbol >= 29) return false;
        uint32_t extra = 0;
        if (!Bits(kLenExtra[symbol], &extra)) return false;
        const size_t length = kLens[symbol] + extra;
        const int dist_symbol = Decode(distcode);
        if (dist_symbol < 0 || dist_symbol >= kDistCodes) return false;
        if (!Bits(kDistExtra[dist_symbol], &extra)) return false;
        const size_t dist = kDists[dist_symbol] + extra;
        if (dist > out_->size()) return false;
        if (out_->size() + length > kMaxOutput) return false;
        // The copy may overlap itself, so it goes byte by byte.
        size_t from = out_->size() - dist;
        for (size_t i = 0; i < length; ++i) out_->push_back((*out_)[from + i]);
      }
    }
  }

  bool Stored() {
    bitbuf_ = 0;  // stored blocks start on a byte boundary
    bitcnt_ = 0;
    if (pos_ + 4 > size_) return false;
    const uint32_t len = in_[pos_] | (uint32_t(in_[pos_ + 1]) << 8);
    const uint32_t inverse = in_[pos_ + 2] | (uint32_t(in_[pos_ + 3]) << 8);
    pos_ += 4;
    if (len != (~inverse & 0xFFFF)) return false;
    if (pos_ + len > size_ || out_->size() + len > kMaxOutput) return false;
    out_->insert(out_->end(), in_ + pos_, in_ + pos_ + len);
    pos_ += len;
    return true;
  }

  bool Fixed() {
    static bool built = false;
    static Huffman lencode, distcode;
    if (!built) {
      uint16_t lengths[kLitLenCodes];
      int s = 0;
      for (; s < 144; ++s) lengths[s] = 8;
      for (; s < 256; ++s) lengths[s] = 9;
      for (; s < 280; ++s) lengths[s] = 7;
      for (; s < kLitLenCodes; ++s) lengths[s] = 8;
      Construct(&lencode, lengths, kLitLenCodes);
      for (s = 0; s < kDistCodes; ++s) lengths[s] = 5;
      Construct(&distcode, lengths, kDistCodes);
      built = true;
    }
    return Codes(lencode, distcode);
  }

  bool Dynamic() {
    static const uint8_t kOrder[19] = {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};
    uint32_t nlen = 0, ndist = 0, ncode = 0;
    if (!Bits(5, &nlen) || !Bits(5, &ndist) || !Bits(4, &ncode)) return false;
    nlen += 257;
    ndist += 1;
    ncode += 4;
    if (nlen > 286 || ndist > kDistCodes) return false;
    uint16_t lengths[320] = {};
    for (uint32_t i = 0; i < ncode; ++i) {
      uint32_t v = 0;
      if (!Bits(3, &v)) return false;
      lengths[kOrder[i]] = static_cast<uint16_t>(v);
    }
    for (uint32_t i = ncode; i < 19; ++i) lengths[kOrder[i]] = 0;
    Huffman lencode, distcode;
    if (Construct(&lencode, lengths, 19) != 0) return false;  // the code-length code must be complete

    uint32_t index = 0;
    while (index < nlen + ndist) {
      const int symbol = Decode(lencode);
      if (symbol < 0) return false;
      if (symbol < 16) {
        lengths[index++] = static_cast<uint16_t>(symbol);
        continue;
      }
      uint16_t previous = 0;
      uint32_t repeat = 0;
      if (symbol == 16) {
        if (index == 0) return false;
        previous = lengths[index - 1];
        if (!Bits(2, &repeat)) return false;
        repeat += 3;
      } else if (symbol == 17) {
        if (!Bits(3, &repeat)) return false;
        repeat += 3;
      } else {
        if (!Bits(7, &repeat)) return false;
        repeat += 11;
      }
      if (index + repeat > nlen + ndist) return false;
      while (repeat--) lengths[index++] = previous;
    }
    if (lengths[256] == 0) return false;  // an end-of-block code is required

    // An incomplete code is only allowed for a single code of length one.
    int err = Construct(&lencode, lengths, static_cast<int>(nlen));
    if (err < 0 || (err > 0 && static_cast<int>(nlen) != lencode.count[0] + lencode.count[1])) return false;
    err = Construct(&distcode, lengths + nlen, static_cast<int>(ndist));
    if (err < 0 || (err > 0 && static_cast<int>(ndist) != distcode.count[0] + distcode.count[1])) return false;
    return Codes(lencode, distcode);
  }

  const uint8_t* in_;
  size_t size_;
  size_t pos_ = 0;
  uint32_t bitbuf_ = 0;
  int bitcnt_ = 0;
  std::vector<uint8_t>* out_;
};

uint32_t Adler32(const std::vector<uint8_t>& data) {
  uint32_t a = 1, b = 0;
  for (uint8_t byte : data) {
    a = (a + byte) % 65521;
    b = (b + a) % 65521;
  }
  return (b << 16) | a;
}

}  // namespace

bool InflateRaw(const uint8_t* data, size_t size, size_t expected, std::vector<uint8_t>* out) {
  out->clear();
  out->reserve(expected);
  Decoder decoder(data, size, out);
  if (!decoder.Run()) {
    out->clear();
    return false;
  }
  return true;
}

bool Inflate(const uint8_t* zlib_data, size_t size, std::vector<uint8_t>* out) {
  out->clear();
  if (size < 6) return false;
  const uint8_t cmf = zlib_data[0], flg = zlib_data[1];
  if ((cmf & 0x0F) != 8 || (cmf >> 4) > 7) return false;      // deflate, window up to 32 KB
  if (((uint32_t(cmf) << 8) | flg) % 31 != 0) return false;   // header check bits
  if (flg & 0x20) return false;                               // a preset dictionary is not supported
  Decoder decoder(zlib_data + 2, size - 2, out);
  if (!decoder.Run()) {
    out->clear();
    return false;
  }
  // The Adler-32 of the output follows the compressed data.
  const size_t at = 2 + decoder.consumed();
  if (at + 4 > size) {
    out->clear();
    return false;
  }
  const uint32_t expected = (uint32_t(zlib_data[at]) << 24) | (uint32_t(zlib_data[at + 1]) << 16) |
                            (uint32_t(zlib_data[at + 2]) << 8) | zlib_data[at + 3];
  if (Adler32(*out) != expected) {
    out->clear();
    return false;
  }
  return true;
}

}  // namespace hexic
