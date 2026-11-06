#pragma once
// Default player names. A new install (or a saved name left empty) gets one of
// these at random instead of the Windows account name, which players may not
// want shown on High Scores. All fit the 15-character name limit.

#include <array>
#include <random>
#include <string>
#include <string_view>

namespace hexic_player_names {

inline constexpr std::array<std::string_view, 50> kNames = {
    "Blockhead",     "Hexxy",        "Hexic Harry",   "Hex Wizard",    "Hex Lord",
    "Hex Machine",   "Hex Appeal",   "Hex Yeah",      "Hexcellent",    "Hex Factor",
    "Hex McGee",     "Puzzle Bob",   "Hexpert",       "Hexzilla",      "Hexen",
    "Blockface",     "Blockbuster",  "Block Party",   "Blockhead Bob", "Blox",
    "Bloxxy",        "Bloxworth",    "Tileman",       "Spinny",        "Spinster",
    "Rotator",       "Clockwise",    "Anticlockwise", "Combobreaker",  "Combobob",
    "Combo Carl",    "Matchstick",   "Matchmaker",    "Matcho",        "Starflower",
    "Flower Power",  "Pearl Jam",    "Black Pearl",   "Pearl Diver",   "Pearl Pete",
    "Bombastic",     "Boomer",       "Bomb Bob",      "Tick Tock",     "No Mover",
    "One More Go",   "Brain Freeze", "Old Mate",      "Link",          "Caius",
};

inline std::string Random() {
  std::random_device device;
  std::uniform_int_distribution<size_t> pick(0, kNames.size() - 1);
  return std::string(kNames[pick(device)]);
}

}  // namespace hexic_player_names
