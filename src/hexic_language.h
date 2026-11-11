#pragma once
// Settings > Language. Hexic HD ships nine translations: g.xml (English) and
// de_ es_ fr_ it_ ja_ ko_ pt_ zh_g.xml beside it in the assets. The game asks
// XGetLanguage once, as it starts, and loads "<code>_g.xml" for that language
// (falling back to the plain name). The SDK answers XGetLanguage from the
// user_language cvar, which OnPostSetup sets from hexic_language, so a change
// applies the next time the game starts.
//
// The port's own wording (Settings, High Scores, Quit Hexic, the keyboard and
// mouse prompts) is written into the translations here, as the game starts:
// each rule names the element around a <text> (the same in every file, unlike
// _locID, which is blank or shared in places) and sets its whole text, or
// swaps a phrase inside it. English keeps its own phrase rules
// (hexic_title.h, and the launcher's import-time relabels).

#include <windows.h>

#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <fmt/format.h>
#include <rex/cvar.h>
#include <rex/logging.h>

REXCVAR_DECLARE(std::string, hexic_language);

namespace hexic_language {

// The Settings row's choices, in order. The Settings font has Latin letters
// only, so Japanese, Korean and Chinese are named in English.
struct Language {
  const char* code;  // hexic_language value; also the file prefix
  const char* name;  // shown in Settings
  uint32_t xlanguage;  // what XGetLanguage returns (1 English ... 9 Portuguese)
};
inline constexpr Language kLanguages[] = {
    {"auto", "Auto", 0},
    {"en", "English", 1},
    {"de", "Deutsch", 3},
    {"es", "Espa\xC3\xB1ol", 5},
    {"fr", "Fran\xC3\xA7" "ais", 4},
    {"it", "Italiano", 6},
    {"pt", "Portugu\xC3\xAAs", 9},
    {"ja", "Japanese", 2},
    {"ko", "Korean", 7},
    {"zh", "Chinese", 8},
};
inline constexpr int kLanguageCount = int(sizeof(kLanguages) / sizeof(kLanguages[0]));

inline int IndexOf(const std::string& code) {
  for (int i = 0; i < kLanguageCount; ++i) {
    if (code == kLanguages[i].code) return i;
  }
  return 0;
}

// Auto: the Windows display language, or English when the game has no
// translation for it (Chinese of any kind gets the Traditional one it has).
inline int AutoIndex() {
  switch (PRIMARYLANGID(GetUserDefaultUILanguage())) {
    case LANG_GERMAN: return IndexOf("de");
    case LANG_SPANISH: return IndexOf("es");
    case LANG_FRENCH: return IndexOf("fr");
    case LANG_ITALIAN: return IndexOf("it");
    case LANG_PORTUGUESE: return IndexOf("pt");
    case LANG_JAPANESE: return IndexOf("ja");
    case LANG_KOREAN: return IndexOf("ko");
    case LANG_CHINESE: return IndexOf("zh");
    default: return IndexOf("en");
  }
}

// The language the game is told to use: the setting, with Auto resolved.
inline const Language& Effective() {
  int index = IndexOf(REXCVAR_GET(hexic_language));
  if (index == 0) index = AutoIndex();
  return kLanguages[index];
}

// ---------------------------------------------------------------- text --

struct Rule {
  const char* element;  // the element around the <text>
  const char* from;     // nullptr: set the whole text; otherwise swap this phrase
  const char* to;
};

// Prompts that differ for a controller and the keyboard and mouse: `pad` is the
// game's own text, `keys` the PC form. Whole text when `whole` is set.
struct Prompt {
  const char* element;
  bool whole;
  const char* pad;
  const char* keys;
};

struct Translation {
  const char* code;
  const Rule* rules;
  int rule_count;
  const Prompt* prompts;
  int prompt_count;
};

// The phrase inside nameEntry_signin and the tutorial cards is swapped in
// place; the four tutorial elements share one prompt each.
#define HEXIC_ROTATE(pad, keys)                                         \
  {"mara_1_body1", false, pad, keys}, {"time_1_body1", false, pad, keys}, \
      {"surv_1_body1", false, pad, keys}, { "Tip_0_Text", false, pad, keys }

inline constexpr Rule kDeRules[] = {
    {"menuButton_achievements", nullptr, "Einstellungen"},
    {"main_achievementstip_text", nullptr, "\xC3\x84ndern Sie Anzeige-, Grafik- und Tastatureinstellungen."},
    {"menuButton_exittodash", nullptr, "Hexic beenden"},
    {"main_exittodashtooltip_text", nullptr, "Beenden Sie HEXIC und kehren Sie zum Desktop zur\xC3\xBC" "ck."},
    {"menuButton_leaderboard", nullptr, "Bestenliste"},
    {"main_leaderboardtooltip_text", nullptr, "Sehen Sie sich Ihre Bestergebnisse in jedem Modus an."},
    {"nameEntry_newscore", nullptr, "Herzlichen Gl\xC3\xBC" "ckwunsch! Sie haben ein neues Bestergebnis!"},
    {"Leaderboard_Sort_Text", nullptr, ""},
    {"Leaderboard_NoScores_Text", nullptr, "Noch keine Bestergebnisse in diesem Modus."},
    {"Leaderboard_SignedIn_Text", nullptr, "Spieler:"},
    {"menuButton_options", nullptr, "Spieloptionen"},
    {"main_optionstooltip_text", nullptr,
     "\xC3\x84ndern Sie Ton und Steinmuster und sehen Sie sich an, wer an diesem Spiel mitgewirkt hat."},
    {"tip_2_body2", "das Optionen-Men\xC3\xBC", "das Spieloptionen-Men\xC3\xBC"},
    {"nameEntry_signin",
     "Dr\xC3\xBC" "cken Sie die Xbox Guide-Taste, um sich bei Xbox Live anzumelden und Ihr Ergebnis hochzuladen!",
     "Ihr Ergebnis kommt in die Bestenliste."},
};
inline constexpr Prompt kDePrompts[] = {
    {"startup_text", true, "Dr\xC3\xBC" "cken Sie A, um fortzufahren.",
     "Dr\xC3\xBC" "cken Sie eine beliebige Taste, um fortzufahren."},
    HEXIC_ROTATE("Drehen Sie die Gruppe mit A im oder mit X entgegen dem Uhrzeigersinn. Sie k\xC3\xB6nnen zum "
                 "Drehen auch einen Schalter ziehen.",
                 "Drehen Sie die Gruppe mit E oder Linksklick im und mit Q oder Rechtsklick entgegen dem "
                 "Uhrzeigersinn."),
};

inline constexpr Rule kEsRules[] = {
    {"menuButton_achievements", nullptr, "Ajustes"},
    {"main_achievementstip_text", nullptr, "Cambia los ajustes de pantalla, gr\xC3\xA1" "ficos y teclado."},
    {"menuButton_exittodash", nullptr, "Salir de Hexic"},
    {"main_exittodashtooltip_text", nullptr, "Salir de Hexic y volver al escritorio."},
    {"menuButton_leaderboard", nullptr, "R\xC3\xA9" "cords"},
    {"main_leaderboardtooltip_text", nullptr, "Consulta tus mejores puntuaciones en cada modo."},
    {"nameEntry_newscore", nullptr, "\xC2\xA1" "Enhorabuena! \xC2\xA1" "Has alcanzado una nueva puntuaci\xC3\xB3n m\xC3\xA1xima!"},
    {"Leaderboard_Sort_Text", nullptr, ""},
    {"Leaderboard_NoScores_Text", nullptr, "A\xC3\xBAn no hay puntuaciones en este modo."},
    {"Leaderboard_SignedIn_Text", nullptr, "Jugador:"},
    {"menuButton_options", nullptr, "Opciones de juego"},
    {"main_optionstooltip_text", nullptr,
     "Cambia el sonido y el patr\xC3\xB3n de las piezas, y consulta qui\xC3\xA9n ha creado este juego."},
    {"tip_2_body2", "men\xC3\xBA Opciones", "men\xC3\xBA Opciones de juego"},
    {"nameEntry_signin", "Pulsar el bot\xC3\xB3n Gu\xC3\xAD" "a Xbox para iniciar sesi\xC3\xB3n en Xbox Live y publicar tu puntuaci\xC3\xB3n.",
     "Tu puntuaci\xC3\xB3n aparecer\xC3\xA1 en R\xC3\xA9" "cords."},
};
inline constexpr Prompt kEsPrompts[] = {
    {"startup_text", true, "Pulsar A para continuar.", "Pulsa cualquier tecla para continuar."},
    HEXIC_ROTATE("Pulsa el bot\xC3\xB3n A para girar al grupo en sentido horario o el bot\xC3\xB3n X para girar en "
                 "sentido contrahorario. O pulsa cualquier gatillo para hacer girar las piezas.",
                 "Pulsa E o haz clic izquierdo para girar el grupo en sentido horario, o pulsa Q o haz clic "
                 "derecho para girarlo en sentido contrahorario."),
};

inline constexpr Rule kFrRules[] = {
    {"menuButton_achievements", nullptr, "Param\xC3\xA8tres"},
    {"main_achievementstip_text", nullptr, "Modifier les param\xC3\xA8tres d'affichage, graphiques et clavier."},
    {"menuButton_exittodash", nullptr, "Quitter Hexic"},
    {"main_exittodashtooltip_text", nullptr, "Quittez Hexic et retournez au bureau."},
    {"menuButton_leaderboard", nullptr, "Meilleurs scores"},
    {"main_leaderboardtooltip_text", nullptr, "Afficher vos meilleurs scores dans chaque mode."},
    {"nameEntry_newscore", nullptr, "F\xC3\xA9licitations ! Vous avez \xC3\xA9tabli un nouveau record !"},
    {"Leaderboard_Sort_Text", nullptr, ""},
    {"Leaderboard_NoScores_Text", nullptr, "Aucun score pour ce mode pour l'instant."},
    {"Leaderboard_SignedIn_Text", nullptr, "Joueur :"},
    {"menuButton_options", nullptr, "Options de jeu"},
    {"main_optionstooltip_text", nullptr,
     "Modifier le son et le motif des pi\xC3\xA8" "ces, et afficher la liste des cr\xC3\xA9" "ateurs de ce jeu."},
    {"tip_2_body2", "menu Options", "menu Options de jeu"},
    // (The original ends in a non-breaking space and "!", which stay.)
    {"nameEntry_signin",
     "Appuyez sur la touche Xbox Guide pour vous connecter \xC3\xA0 Xbox Live et publier votre score",
     "Votre score figure parmi les meilleurs scores"},
};
inline constexpr Prompt kFrPrompts[] = {
    {"startup_text", true, "Appuyez sur A pour continuer.", "Appuyez sur une touche pour continuer."},
    HEXIC_ROTATE("Appuyez sur A ou D pour les faire pivoter dans le sens horaire, sur X ou G dans le sens inverse.",
                 "Appuyez sur E ou faites un clic gauche pour les faire pivoter dans le sens horaire, sur Q ou "
                 "faites un clic droit dans le sens inverse."),
};

inline constexpr Rule kItRules[] = {
    {"menuButton_achievements", nullptr, "Impostazioni"},
    {"main_achievementstip_text", nullptr, "Modifica le impostazioni di schermo, grafica e tastiera."},
    {"menuButton_exittodash", nullptr, "Esci da Hexic"},
    {"main_exittodashtooltip_text", nullptr, "Esci da Hexic e torna al desktop."},
    {"menuButton_leaderboard", nullptr, "Record"},
    {"main_leaderboardtooltip_text", nullptr, "Visualizza i tuoi record per ogni modalit\xC3\xA0."},
    {"Leaderboard_Sort_Text", nullptr, ""},
    {"Leaderboard_NoScores_Text", nullptr, "Ancora nessun record per questa modalit\xC3\xA0."},
    {"Leaderboard_SignedIn_Text", nullptr, "Giocatore:"},
    {"menuButton_options", nullptr, "Opzioni di gioco"},
    {"main_optionstooltip_text", nullptr, "Modifica l'audio e i simboli dei pezzi e guarda chi ha creato questo gioco."},
    {"tip_2_body2", "menu Opzioni", "menu Opzioni di gioco"},
    {"nameEntry_signin", "Premi il pulsante Guida Xbox per connetterti a Xbox Live e inviare il tuo punteggio!!!",
     "Il tuo punteggio entra nei record!"},
};
inline constexpr Prompt kItPrompts[] = {
    {"startup_text", true, "Premi A per continuare.", "Premi un tasto qualsiasi per continuare."},
    HEXIC_ROTATE("Premi A per ruotare il gruppo in senso orario, X per ruotarlo in senso antiorario o premi "
                 "entrambi i grilletti per ruotare i pezzi.",
                 "Premi E o fai clic sinistro per ruotare il gruppo in senso orario, Q o clic destro per "
                 "ruotarlo in senso antiorario."),
};

inline constexpr Rule kPtRules[] = {
    {"menuButton_achievements", nullptr, "Configura\xC3\xA7\xC3\xB5" "es"},
    {"main_achievementstip_text", nullptr, "Altere as configura\xC3\xA7\xC3\xB5" "es de tela, gr\xC3\xA1" "ficos e teclado."},
    {"menuButton_exittodash", nullptr, "Sair do Hexic"},
    {"main_exittodashtooltip_text", nullptr, "Sair do Hexic e voltar para a \xC3\xA1rea de trabalho."},
    {"menuButton_leaderboard", nullptr, "Recordes"},
    {"main_leaderboardtooltip_text", nullptr, "Ver suas melhores pontua\xC3\xA7\xC3\xB5" "es em cada modo."},
    {"nameEntry_newscore", nullptr, "Parab\xC3\xA9ns! Voc\xC3\xAA tem uma nova pontua\xC3\xA7\xC3\xA3o alta!"},
    {"Leaderboard_Sort_Text", nullptr, ""},
    {"Leaderboard_NoScores_Text", nullptr, "Ainda n\xC3\xA3o h\xC3\xA1 recordes para este modo."},
    {"Leaderboard_SignedIn_Text", nullptr, "Jogador:"},
    {"menuButton_options", nullptr, "Op\xC3\xA7\xC3\xB5" "es do jogo"},
    {"main_optionstooltip_text", nullptr,
     "Modifique o som e o padr\xC3\xA3o das pe\xC3\xA7" "as, e veja quem fez este jogo."},
    {"tip_2_body2", "menu Op\xC3\xA7\xC3\xB5" "es", "menu Op\xC3\xA7\xC3\xB5" "es do jogo"},
    {"nameEntry_signin",
     "Pressione o bot\xC3\xA3o Painel Xbox para se conectar ao Xbox Live e adicionar a pontua\xC3\xA7\xC3\xA3o!!",
     "Sua pontua\xC3\xA7\xC3\xA3o vai para os Recordes!"},
};
inline constexpr Prompt kPtPrompts[] = {
    {"startup_text", true, "Pressione A para continuar.", "Pressione qualquer tecla para continuar."},
    HEXIC_ROTATE("Pressione A para girar o grupo no sentido do rel\xC3\xB3gio, ou X no sentido contr\xC3\xA1rio.",
                 "Pressione E ou clique com o bot\xC3\xA3o esquerdo para girar o grupo no sentido do rel\xC3\xB3gio, "
                 "ou Q ou o bot\xC3\xA3o direito no sentido contr\xC3\xA1rio."),
};

// Japanese, Korean and Chinese are kept in their own UTF-8 below (the source is
// UTF-8 and clang keeps narrow literals as written).
inline constexpr Rule kJaRules[] = {
    {"menuButton_achievements", nullptr, "設定"},
    {"main_achievementstip_text", nullptr, "画面、グラフィック、キーボードの設定を変更しよう"},
    {"menuButton_exittodash", nullptr, "Hexic を終了"},
    {"main_exittodashtooltip_text", nullptr, "Hexic を終了し、デスクトップに戻る"},
    {"menuButton_leaderboard", nullptr, "ハイスコア"},
    {"main_leaderboardtooltip_text", nullptr, "モードごとのハイスコアを見る"},
    {"nameEntry_newscore", nullptr, "おめでとう! ハイスコアを更新しました!!"},
    {"Leaderboard_Sort_Text", nullptr, ""},
    {"Leaderboard_NoScores_Text", nullptr, "このモードには、まだ\nスコアがありません。"},
    {"Leaderboard_SignedIn_Text", nullptr, "名前 :"},
    {"menuButton_options", nullptr, "ゲーム オプション"},
    {"main_optionstooltip_text", nullptr, "サウンドとタイルのパターンを変更しよう"},
    {"nameEntry_signin", "スコアを登録するには、Xbox ガイド ボタンを押して Xbox Live にログインしてください。",
     "スコアはハイスコアに記録されます。"},
};
inline constexpr Prompt kJaPrompts[] = {
    {"startup_text", true, "A ボタンを押して続けてください", "いずれかのキーを押して続けてください"},
    HEXIC_ROTATE("A ボタンを押すと右方向に、X ボタンを押すと左方向に回転します。また、右または左トリガでも回転させることができます。",
                 "E キーか左クリックで右方向に、Q キーか右クリックで左方向に回転します。"),
};

inline constexpr Rule kKoRules[] = {
    {"menuButton_achievements", nullptr, "설정"},
    {"main_achievementstip_text", nullptr, "화면, 그래픽, 키보드 설정을 바꿉니다."},
    {"menuButton_exittodash", nullptr, "Hexic 종료"},
    {"main_exittodashtooltip_text", nullptr, "Hexic을 종료하고 바탕 화면으로 돌아갑니다."},
    {"menuButton_leaderboard", nullptr, "최고 점수"},
    {"main_leaderboardtooltip_text", nullptr, "모드별 최고 점수를 봅니다."},
    {"nameEntry_newscore", nullptr, "축하합니다! 최고 점수를 기록했습니다!"},
    {"Leaderboard_Sort_Text", nullptr, ""},
    {"Leaderboard_NoScores_Text", nullptr, "이 모드에는 아직 최고 점수가 없습니다."},
    {"Leaderboard_SignedIn_Text", nullptr, "플레이어:"},
    {"menuButton_options", nullptr, "게임 옵션"},
    {"main_optionstooltip_text", nullptr, "소리와 조각 패턴을 바꾸고 이 게임의 제작진을 봅니다."},
    {"tip_2_body2", "옵션 메뉴", "게임 옵션 메뉴"},
    {"nameEntry_signin", "점수를 등록하려면 Xbox 가이드 단추를 눌러 Xbox Live에 로그인하세요.",
     "점수가 최고 점수 목록에 기록됩니다."},
};
inline constexpr Prompt kKoPrompts[] = {
    {"startup_text", true, "계속하려면 A 단추를 누르십시오.", "계속하려면 아무 키나 누르십시오."},
    HEXIC_ROTATE("A 단추를 누르면 클러스터가 시계 방향으로 회전하고 X 단추를 누르면 시계 반대 방향으로 회전합니다. 트리거를 당겨도 회전합니다.",
                 "E 키나 마우스 왼쪽 단추를 누르면 클러스터가 시계 방향으로 회전하고 Q 키나 마우스 오른쪽 단추를 누르면 시계 반대 방향으로 회전합니다."),
};

inline constexpr Rule kZhRules[] = {
    {"menuButton_achievements", nullptr, "設定"},
    {"main_achievementstip_text", nullptr, "變更顯示、圖形及按鍵設定。"},
    {"menuButton_exittodash", nullptr, "離開 Hexic"},
    {"main_exittodashtooltip_text", nullptr, "離開 Hexic 回到 Windows。"},
    {"menuButton_leaderboard", nullptr, "高分紀錄"},
    {"main_leaderboardtooltip_text", nullptr, "查閱每個模式的最高分紀錄。"},
    {"nameEntry_newscore", nullptr, "恭喜 ! 你剛創下新的高分紀錄 ! "},
    {"Leaderboard_Sort_Text", nullptr, ""},
    {"Leaderboard_NoScores_Text", nullptr, "此模式尚無高分紀錄。"},
    {"Leaderboard_SignedIn_Text", nullptr, "玩家 :"},
    {"menuButton_options", nullptr, "遊戲選項"},
    {"main_optionstooltip_text", nullptr, "變更音樂及方塊樣式, 並參觀製作小組。"},
    {"tip_2_body2", "從選項選單中", "從遊戲選項選單中"},
    {"nameEntry_signin", "按下 360 按鍵登入 Xbox Live 來登記你的成績 ! ", "你的成績已登記在高分紀錄中 ! "},
};
inline constexpr Prompt kZhPrompts[] = {
    {"startup_text", true, "按 A 按鍵繼續。", "按任意鍵繼續。"},
    HEXIC_ROTATE("按 A 按鍵順時針旋轉, 按 X 按鍵逆時針旋轉, 或按左右發射鍵來旋轉。",
                 "按 E 鍵或左鍵順時針旋轉, 按 Q 鍵或右鍵逆時針旋轉。"),
};

#undef HEXIC_ROTATE

#define HEXIC_TRANSLATION(code, rules, prompts) \
  { code, rules, int(sizeof(rules) / sizeof(rules[0])), prompts, int(sizeof(prompts) / sizeof(prompts[0])) }
inline constexpr Translation kTranslations[] = {
    HEXIC_TRANSLATION("de", kDeRules, kDePrompts), HEXIC_TRANSLATION("es", kEsRules, kEsPrompts),
    HEXIC_TRANSLATION("fr", kFrRules, kFrPrompts), HEXIC_TRANSLATION("it", kItRules, kItPrompts),
    HEXIC_TRANSLATION("pt", kPtRules, kPtPrompts), HEXIC_TRANSLATION("ja", kJaRules, kJaPrompts),
    HEXIC_TRANSLATION("ko", kKoRules, kKoPrompts), HEXIC_TRANSLATION("zh", kZhRules, kZhPrompts),
};
#undef HEXIC_TRANSLATION

// The text of every <text> directly inside <element>: [begin, end) offsets of
// the visible text (after an optional <!-- comment -->). Calls `edit` for each,
// last first, so offsets stay valid while it edits.
template <typename Edit>
inline void ForEachText(std::string& xml, const char* element, Edit edit) {
  const std::string open = std::string("<") + element + ">";
  std::vector<std::pair<size_t, size_t>> spans;
  for (size_t at = xml.find(open); at != std::string::npos; at = xml.find(open, at + open.size())) {
    const size_t text = xml.find("<text", at);
    const size_t close_element = xml.find(std::string("</") + element + ">", at);
    if (text == std::string::npos || (close_element != std::string::npos && text > close_element)) continue;
    size_t begin = xml.find('>', text);
    if (begin == std::string::npos) continue;
    ++begin;
    if (xml.compare(begin, 4, "<!--") == 0) {
      const size_t comment_end = xml.find("-->", begin);
      if (comment_end == std::string::npos) continue;
      begin = comment_end + 3;
    }
    const size_t end = xml.find("</text>", begin);
    if (end == std::string::npos) continue;
    spans.emplace_back(begin, end);
  }
  for (auto it = spans.rbegin(); it != spans.rend(); ++it) edit(it->first, it->second);
}

// Writes the PC wording into one translation; `controller` picks the prompts.
// Returns how many rules found nothing to match (logged: a sign the file is not
// the expected one). Every rule is a no-op once applied.
inline int ApplyTranslation(std::string& xml, const Translation& t, bool controller, bool* changed) {
  int missed = 0;
  auto set_whole = [&](const char* element, const std::string& to) {
    bool found = false;
    ForEachText(xml, element, [&](size_t begin, size_t end) {
      found = true;
      if (xml.compare(begin, end - begin, to) != 0) {
        xml.replace(begin, end - begin, to);
        *changed = true;
      }
    });
    return found;
  };
  // Swaps `from` for `to` inside the element; true if either is there. `to` is
  // looked for first: some contain `from` ("menu Options de jeu").
  auto swap_phrase = [&](const char* element, const std::string& from, const std::string& to) {
    bool found = false;
    ForEachText(xml, element, [&](size_t begin, size_t end) {
      const std::string text = xml.substr(begin, end - begin);
      if (text.find(to) != std::string::npos) {
        found = true;
        return;
      }
      const size_t at = text.find(from);
      if (at != std::string::npos) {
        xml.replace(begin + at, from.size(), to);
        *changed = true;
        found = true;
      }
    });
    return found;
  };
  for (int i = 0; i < t.rule_count; ++i) {
    const Rule& r = t.rules[i];
    const bool ok = r.from ? swap_phrase(r.element, r.from, r.to) : set_whole(r.element, r.to);
    if (!ok) {
      ++missed;
      REXLOG_WARN("[language] {}_g.xml: no match for {}", t.code, r.element);
    }
  }
  for (int i = 0; i < t.prompt_count; ++i) {
    const Prompt& p = t.prompts[i];
    const char* want = controller ? p.pad : p.keys;
    const char* other = controller ? p.keys : p.pad;
    const bool ok = p.whole ? set_whole(p.element, want) : swap_phrase(p.element, other, want);
    if (!ok) {
      ++missed;
      REXLOG_WARN("[language] {}_g.xml: no match for {}", t.code, p.element);
    }
  }
  return missed;
}

// Every translation present in the assets gets the PC wording (all of them, so
// switching language needs nothing more than a restart).
inline void ApplyTranslations(const std::filesystem::path& assets, bool controller) {
  for (const Translation& t : kTranslations) {
    const auto path = assets / (std::string(t.code) + "_g.xml");
    std::ifstream in(path, std::ios::binary);
    if (!in) continue;
    std::stringstream buffer;
    buffer << in.rdbuf();
    in.close();
    std::string xml = buffer.str();
    bool changed = false;
    const int missed = ApplyTranslation(xml, t, controller, &changed);
    if (changed) {
      std::ofstream out(path, std::ios::binary | std::ios::trunc);
      out.write(xml.data(), static_cast<std::streamsize>(xml.size()));
    }
    if (changed || missed) {
      REXLOG_INFO("[language] {}_g.xml: PC wording {}{}", t.code, changed ? "applied" : "already applied",
                  missed ? fmt::format(", {} rule(s) unmatched", missed) : std::string());
    }
  }
}

}  // namespace hexic_language
