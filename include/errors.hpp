// xs_errors.h
#pragma once
#include <3ds.h>
#include <string>
#include <unordered_map>

namespace xs::errors {

// Lookup tables
static const std::unordered_map<int, const char *> levelNames = {
    {0, "Success"},         {1, "Info"},
    {0x1F, "Fatal"},        {0x1E, "Reset"},
    {0x1D, "Reinitialize"}, {0x1C, "Usage"},
    {0x1B, "Permanent"},    {0x1A, "Temporary"},
    {0x19, "Status"}};

static const std::unordered_map<int, const char *> summaryNames = {
    {0, "Success"},
    {1, "No operation"},
    {2, "Would block"},
    {3, "Out of resource"},
    {4, "Not found"},
    {5, "Invalid state"},
    {6, "Not supported"},
    {7, "Invalid argument"},
    {8, "Wrong argument"},
    {9, "Canceled"},
    {10, "Status changed"},
    {11, "Internal"},
    {63, "Invalid result value"}};

static const std::unordered_map<int, const char *> moduleNames = {
    {0, "Common"},
    {1, "Kernel"},
    {2, "Util"},
    {3, "File Server"},
    {4, "Loader Server"},
    {5, "TCB"},
    {6, "OS"},
    {7, "DBG"},
    {8, "DMNT"},
    {9, "PDN"},
    {10, "GSP"},
    {11, "I2C"},
    {12, "GPIO"},
    {13, "DD"},
    {14, "Codec"},
    {15, "SPI"},
    {16, "PXI"},
    {17, "FS"},
    {18, "DI"},
    {19, "HID"},
    {20, "CAM"},
    {21, "PI"},
    {22, "PM"},
    {23, "PM Low"},
    {24, "FSI"},
    {25, "SRV"},
    {26, "NDM"},
    {27, "NWM"},
    {28, "SOC"},
    {29, "LDR"},
    {30, "ACC"},
    {31, "ROMFS"},
    {32, "AM"},
    {33, "HIO"},
    {34, "Updater"},
    {35, "MIC"},
    {36, "FND"},
    {37, "MP"},
    {38, "MPWL"},
    {39, "AC"},
    {40, "HTTP"},
    {41, "DSP"},
    {42, "SND"},
    {43, "DLP"},
    {44, "HIO Low"},
    {45, "CSND"},
    {46, "SSL"},
    {47, "AM Low"},
    {48, "NEX"},
    {49, "Friends"},
    {50, "RDT"},
    {51, "Applet"},
    {52, "NIM"},
    {53, "PTM"},
    {54, "MIDI"},
    {55, "MC"},
    {56, "SWC"},
    {57, "FATFS"},
    {58, "NGC"},
    {59, "Card"},
    {60, "CardNOR"},
    {61, "SDMC"},
    {62, "BOSS"},
    {63, "DBM"},
    {64, "Config"},
    {65, "PS"},
    {66, "CEC"},
    {67, "IR"},
    {68, "UDS"},
    {69, "PL"},
    {70, "CUP"},
    {71, "Gyroscope"},
    {72, "MCU"},
    {73, "NS"},
    {74, "News"},
    {75, "RO"},
    {76, "GD"},
    {77, "Card SPI"},
    {78, "EC"},
    {79, "Web Browser"},
    {80, "Test"},
    {81, "ENC"},
    {82, "PIA"},
    {83, "ACT"},
    {84, "VCTL"},
    {85, "OLV"},
    {86, "NEIA"},
    {87, "NPNS"},
    {90, "AVD"},
    {91, "L2B"},
    {92, "MVD"},
    {93, "NFC"},
    {94, "UART"},
    {95, "SPM"},
    {96, "QTM"},
    {97, "NFP"},
    {254, "Application"},
    {255, "Invalid"}};

static const std::unordered_map<int, const char *> descriptionNames = {
    {0, "Success"},
    {0x3FF, "Invalid result value"},
    {0x3FE, "Timeout"},
    {0x3FD, "Out of range"},
    {0x3FC, "Already exists"},
    {0x3FB, "Cancel requested"},
    {0x3FA, "Not found"},
    {0x3F9, "Already initialized"},
    {0x3F8, "Not initialized"},
    {0x3F7, "Invalid handle"},
    {0x3F6, "Invalid pointer"},
    {0x3F5, "Invalid address"},
    {0x3F4, "Not implemented"},
    {0x3F3, "Out of memory"},
    {0x3F2, "Misaligned size"},
    {0x3F1, "Misaligned address"},
    {0x3F0, "Busy"},
    {0x3EF, "No data"},
    {0x3EE, "Invalid combination"},
    {0x3ED, "Invalid enum value"},
    {0x3EC, "Invalid size"},
    {0x3EB, "Already done"},
    {0x3EA, "Not authorized"},
    {0x3E9, "Too large"},
    {0x3E8, "Invalid selection"}};

inline std::string decode(Result res) {
  int lvl = R_LEVEL(res);
  int sum = R_SUMMARY(res);
  int mod = R_MODULE(res);
  int desc = R_DESCRIPTION(res);

  const char *lvlStr = levelNames.count(lvl) ? levelNames.at(lvl) : "Unknown";
  const char *sumStr =
      summaryNames.count(sum) ? summaryNames.at(sum) : "Unknown";
  const char *modStr = moduleNames.count(mod) ? moduleNames.at(mod) : "Unknown";
  const char *descStr =
      descriptionNames.count(desc) ? descriptionNames.at(desc) : "Unknown";

  char buf[512];
  snprintf(buf, sizeof(buf),
           "Result: 0x%08lX\n"
           " Level: %s (%d)\n"
           " Summary: %s (%d)\n"
           " Module: %s (%d)\n"
           " Description: %s (%d)",
           res, lvlStr, lvl, sumStr, sum, modStr, mod, descStr, desc);

  return std::string(buf);
}

inline void show(Result res, bool softwareReset = false) {
  errorConf err;
  errorInit(&err, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
  err.softwareReset = softwareReset;
  std::string msg = decode(res);
  errorText(&err, msg.c_str());
  errorDisp(&err);
}

inline void show(const char *msg, bool softwareReset = false) {
  errorConf err;
  errorInit(&err, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
  err.softwareReset = softwareReset;
  errorText(&err, msg);
  errorDisp(&err);
}

} // namespace xs::errors
