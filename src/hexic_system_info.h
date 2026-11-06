// hexic_hd - log header: what a problem report needs to know about the PC.
//
// Written once at start: Windows, CPU, memory, the GPU and its driver, every
// active display's mode with its exact refresh rate (a "60 Hz" screen is often
// 59.94 or 60.1 Hz) and the settings that change timing. Ported from the
// Perfect Dark port's LogSystemInfo (its HANDOVER 4ak).
#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <dxgi.h>
#include <intrin.h>

#include <cstring>
#include <string>
#include <vector>

#include <fmt/format.h>
#include <rex/cvar.h>
#include <rex/logging.h>

namespace hexic_system_info {

inline std::string Utf8(const wchar_t* text) {
  char out[256] = {};
  WideCharToMultiByte(CP_UTF8, 0, text, -1, out, sizeof(out) - 1, nullptr, nullptr);
  return out;
}

inline std::string WindowsText() {
  using RtlGetVersionFn = LONG(WINAPI*)(OSVERSIONINFOW*);
  HMODULE ntdll = ::GetModuleHandleW(L"ntdll.dll");
  auto get_version =
      ntdll ? reinterpret_cast<RtlGetVersionFn>(::GetProcAddress(ntdll, "RtlGetVersion")) : nullptr;
  OSVERSIONINFOW v{};
  v.dwOSVersionInfoSize = sizeof(v);
  if (!get_version || get_version(&v) != 0) return "unknown";
  DWORD ubr = 0, size = sizeof(ubr);
  RegGetValueW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"UBR",
               RRF_RT_REG_DWORD, nullptr, &ubr, &size);
  // Windows 11 still reports itself as 10.0; its builds start at 22000.
  const bool eleven = v.dwMajorVersion == 10 && v.dwBuildNumber >= 22000;
  return fmt::format("{} {}.{}.{}.{}", eleven ? "Windows 11" : "Windows", v.dwMajorVersion,
                     v.dwMinorVersion, v.dwBuildNumber, ubr);
}

inline std::string CpuText() {
  int regs[4] = {};
  char brand[49] = {};
  __cpuid(regs, int(0x80000000));
  if (unsigned(regs[0]) >= 0x80000004u) {
    for (int i = 0; i < 3; ++i) {
      __cpuid(regs, int(0x80000002 + i));
      std::memcpy(brand + i * 16, regs, 16);
    }
  }
  std::string name = brand;
  name.erase(0, name.find_first_not_of(' '));
  while (!name.empty() && name.back() == ' ') name.pop_back();
  SYSTEM_INFO si{};
  GetSystemInfo(&si);
  ULONGLONG installed_kb = 0;
  if (!GetPhysicallyInstalledSystemMemory(&installed_kb)) {
    MEMORYSTATUSEX mem{};
    mem.dwLength = sizeof(mem);
    GlobalMemoryStatusEx(&mem);
    installed_kb = mem.ullTotalPhys / 1024;
  }
  return fmt::format("{}, {} threads, {:.0f} GB memory", name.empty() ? "unknown" : name,
                     si.dwNumberOfProcessors, double(installed_kb) / (1024.0 * 1024));
}

// The first hardware adapter (the one the game uses) and its driver version.
// DXGI is loaded at run time so nothing links against it.
inline std::string GpuText() {
  HMODULE dxgi = ::LoadLibraryW(L"dxgi.dll");
  if (!dxgi) return {};
  using CreateFactory1Fn = HRESULT(WINAPI*)(REFIID, void**);
  auto create_factory1 =
      reinterpret_cast<CreateFactory1Fn>(::GetProcAddress(dxgi, "CreateDXGIFactory1"));
  std::string text;
  IDXGIFactory1* factory = nullptr;
  if (create_factory1 && SUCCEEDED(create_factory1(IID_PPV_ARGS(&factory))) && factory) {
    IDXGIAdapter1* adapter = nullptr;
    for (UINT i = 0; text.empty() && factory->EnumAdapters1(i, &adapter) == S_OK; ++i) {
      DXGI_ADAPTER_DESC1 desc;
      if (SUCCEEDED(adapter->GetDesc1(&desc)) && !(desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)) {
        LARGE_INTEGER umd{};
        std::string driver = "unknown";
        if (SUCCEEDED(adapter->CheckInterfaceSupport(__uuidof(IDXGIDevice), &umd))) {
          const auto part = [&](int shift) { return unsigned((umd.QuadPart >> shift) & 0xFFFF); };
          driver = fmt::format("{}.{}.{}.{}", part(48), part(32), part(16), part(0));
        }
        text = fmt::format("{} (vendor {:04X}, {} MB), driver {}", Utf8(desc.Description),
                           desc.VendorId, desc.DedicatedVideoMemory / (1024 * 1024), driver);
      }
      adapter->Release();
    }
    factory->Release();
  }
  ::FreeLibrary(dxgi);
  return text;
}

// One line per active display: its name, the monitor's own name, the desktop
// mode and the exact refresh rate (QueryDisplayConfig's fraction).
inline std::vector<std::string> DisplayLines() {
  std::vector<std::string> out;
  UINT32 path_count = 0, mode_count = 0;
  if (GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &path_count, &mode_count) !=
      ERROR_SUCCESS) {
    return out;
  }
  std::vector<DISPLAYCONFIG_PATH_INFO> paths(path_count);
  std::vector<DISPLAYCONFIG_MODE_INFO> modes(mode_count);
  if (QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &path_count, paths.data(), &mode_count,
                         modes.data(), nullptr) != ERROR_SUCCESS) {
    return out;
  }
  paths.resize(path_count);
  for (const auto& path : paths) {
    DISPLAYCONFIG_SOURCE_DEVICE_NAME source{};
    source.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
    source.header.size = sizeof(source);
    source.header.adapterId = path.sourceInfo.adapterId;
    source.header.id = path.sourceInfo.id;
    if (DisplayConfigGetDeviceInfo(&source.header) != ERROR_SUCCESS) source.viewGdiDeviceName[0] = 0;
    DISPLAYCONFIG_TARGET_DEVICE_NAME target{};
    target.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
    target.header.size = sizeof(target);
    target.header.adapterId = path.targetInfo.adapterId;
    target.header.id = path.targetInfo.id;
    if (DisplayConfigGetDeviceInfo(&target.header) != ERROR_SUCCESS) {
      target.monitorFriendlyDeviceName[0] = 0;
    }
    uint32_t width = 0, height = 0;
    const UINT32 index = path.sourceInfo.modeInfoIdx;
    if (index < modes.size() && modes[index].infoType == DISPLAYCONFIG_MODE_INFO_TYPE_SOURCE) {
      width = modes[index].sourceMode.width;
      height = modes[index].sourceMode.height;
    }
    const auto& rate = path.targetInfo.refreshRate;
    const double hz = rate.Denominator ? double(rate.Numerator) / double(rate.Denominator) : 0.0;
    const std::string monitor = Utf8(target.monitorFriendlyDeviceName);
    out.push_back(fmt::format("display {}{}: {} x {} at {:.3f} Hz", Utf8(source.viewGdiDeviceName),
                              monitor.empty() ? std::string() : " (" + monitor + ")", width,
                              height, hz));
  }
  return out;
}

inline void Log() {
  REXLOG_INFO("[system] {}", WindowsText());
  REXLOG_INFO("[system] CPU: {}", CpuText());
  const std::string gpu = GpuText();
  if (!gpu.empty()) REXLOG_INFO("[system] GPU: {}", gpu);
  for (const auto& line : DisplayLines()) REXLOG_INFO("[system] {}", line);
  auto flag = [](const char* name) { return rex::cvar::GetFlagByName(name); };
  REXLOG_INFO("[system] settings: fullscreen {}, vsync {}, fixed guest vblank {}, frame limit {}, "
              "resolution {} x {}, render scale {}x, anti-aliasing {}, upscaling {}, renderer {}",
              flag("fullscreen"), flag("vsync"), flag("fixed_guest_vblank"),
              flag("present_frame_limit"), flag("video_mode_width"), flag("video_mode_height"),
              flag("resolution_scale"), flag("swap_post_effect"), flag("present_effect"),
              flag("gpu"));
}

}  // namespace hexic_system_info
