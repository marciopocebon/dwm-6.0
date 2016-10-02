/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus-medium-r-*-*-16-*-*-*-*-*-*-*"; /* шрифт */
static const char normbordercolor[] = "#444444";    /* цвет границ окна             */
static const char normbgcolor[]     = "#1c1c1c";    /* цвет фона                    */
static const char normfgcolor[]     = "#87AFAF";    /* цвет текста в status bar'e   */
static const char selbordercolor[]  = "#D64937";    /* цвет границ активного окна   */
static const char selbgcolor[]      = "#262626";    /* цвет фона заголовка окна     */
static const char selfgcolor[]      = "#ffffff";    /* цвет текста заголовка окна   */
static const unsigned int borderpx  = 1.5;          /* border pixel of windows      */
static const unsigned int snap      = 32;           /* snap pixel                   */
static const unsigned int systrayspacing = 2;       /* systray spacing              */
static const Bool showsystray       = True;         /* False means no systray       */
static const Bool showbar           = True;         /* False means no bar           */
static const Bool topbar            = False;        /* False means bottom bar       */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
/* class                instance        title           role            tags mask       isfloating      monitor */
 { "Gmusicbrowser",     "gmusicbrowser",NULL,           NULL,           256,            False,          -1 },
 { "Gimp",              NULL,           NULL,           NULL,           0,              True,           -1 },
 { "Lazarus",           NULL,           NULL,           NULL,           0,              True,           -1 },
 { "floaterm",          "xterm",        NULL,           NULL,           0,              True,           -1 },
 { "XBiff",             "xbiff",        "xbiff",        NULL,           ~0,             True,           -1 },
 { "XClock",            "xclock",       "xclock",       NULL,           ~0,             True,           -1 },
 { "XCalc",             "xcalc",        "Calculator",   NULL,           0,              True,           -1 },
 { "Xmessage",          "xmessage",     "xmessage",     NULL,           0,              True,           -1 },

 /* Don't forget to install window_merge plugin */
 { "Pidgin",            NULL,           NULL,           "buddy_list",   0,              False,          1  },
/*
 { "Skype",             NULL,           NULL,          "ConversationsWindow", 2,        False,          1  },
 */
 { "Hexchat",           NULL,           NULL,           NULL,           0,              False,          1  },
 { "Thunderbird",       NULL,           NULL,           NULL,     	2,              False,          1  },
 { "Skype",             NULL,           NULL,           NULL,           4,              False,          1  },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
                                      /* Размер мастер-окна в % от ширины экрана */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False;/* True means respect size hints in tiled resizals */

#include "bstack.c"
#include "bstackhoriz.c"
#include "gaplessgrid.c"
static const Layout layouts[] = {
        /* symbol     arrange function */
        { "[]=",      tile },    /* first entry is default */
        { "><>",      NULL },    /* no layout function means floating behavior */
        { "[M]",      monocle },
        { "TTT",      bstack },
        { "===",      bstackhoriz },
        { "###",      gaplessgrid },
};

/* key definitions */
/* Mod4Mask - Windows key, Mod1Mask - Alt */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
        { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
        { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Для мультимедия клавиатур определения */
#include <X11/XF86keysym.h>

static const char *dmenu_cmd[] = { "dmenu_run",
                                    "-fn", font,
                                    "-nb", normbgcolor,
                                    "-nf", normfgcolor,
                                    "-sb", selbgcolor,
                                    "-sf", selfgcolor, NULL };

static const char *term_cmd[]  = { "xterm", NULL };

static const char *player_prog_cmd[]   = { "gmusicbrowser", NULL };
static const char *player_stop_cmd[]   = { "gmusicbrowser", "-cmd", "Stop",      NULL };
static const char *player_play_cmd[]   = { "gmusicbrowser", "-cmd", "PlayPause", NULL };
static const char *player_prev_cmd[]   = { "gmusicbrowser", "-cmd", "PrevSongInPlaylist", NULL };
static const char *player_next_cmd[]   = { "gmusicbrowser", "-cmd", "NextSongInPlaylist", NULL };
static const char *player_mute_cmd[]   = { "gmusicbrowser", "-cmd", "TogMute",   NULL };
static const char *player_vinc_cmd[]   = { "gmusicbrowser", "-cmd", "IncVolume", NULL };
static const char *player_vdec_cmd[]   = { "gmusicbrowser", "-cmd", "DecVolume", NULL };
static const char *player_quit_cmd[]   = { "gmusicbrowser", "-cmd", "Quit",      NULL };

#define AUDIO_CARD "alsa_output.pci-0000_00_05.0.analog-stereo"

static const char *audio_mute_cmd[] =  { "pactl", "set-sink-mute", AUDIO_CARD, "toggle", NULL };
static const char *audio_lower_cmd[] = { "pactl", "set-sink-volume", AUDIO_CARD, "-1%", NULL };
static const char *audio_raise_cmd[] = { "pactl", "set-sink-volume", AUDIO_CARD, "+1%", NULL };

/*
static const char *master_mute_cmd[]  = { "amixer", "sset", "Master,0", "toggle", NULL };
static const char *master_lower_cmd[] = { "amixer", "sset", "Master,0", "1-", NULL };
static const char *master_raise_cmd[] = { "amixer", "sset", "Master,0", "1+", NULL };
static const char *front_lower_cmd[]  = { "amixer", "sset", "Front", "1-", NULL };
static const char *front_raise_cmd[]  = { "amixer", "sset", "Front", "1+", NULL };
static const char *headphone_l_cmd[]  = { "amixer", "sset", "Headphone,0", "1-", NULL };
static const char *headphone_r_cmd[]  = { "amixer", "sset", "Headphone,0", "1+", NULL };
static const char *fileman_cmd[] = { "xterm", "-e", "mc", "-S", "dark", "/mnt", "~/", NULL };
static const char *browser_cmd[] = { "firefox", NULL };
static const char *email_cmd[]   = { "thunderbird", NULL };
static const char *calcul_cmd[]  = { "xcalc", NULL };
*/

/* Для ноутбуков */
static const char *xbacklightinc_cmd[] = { "xbacklight", "-set", "100", NULL };
static const char *xbacklightdec_cmd[] = { "xbacklight", "-set", "0", NULL };

/*************************************************************************************/

static Key keys[] = {
        /* modifier                     key        function        argument */
        { MODKEY,                       XK_p,      spawn,          {.v = dmenu_cmd } },
        { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = term_cmd } },
        { MODKEY,                       XK_b,      togglebar,      {0} },

        { MODKEY,                       XK_Up,     focusstack,     {.i = +1 } },
        { MODKEY,                       XK_Down,   focusstack,     {.i = -1 } },
//      { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
//      { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
        { MODKEY|ShiftMask,             XK_Left,   setmfact,       {.f = -0.05} },
        { MODKEY|ShiftMask,             XK_Right,  setmfact,       {.f = +0.05} },

        { MODKEY,                       XK_Return, zoom,           {0} },
        { MODKEY,                       XK_Tab,    view,           {0} },
        { MODKEY,                       XK_c,      killclient,     {0} },
        { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
        { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
        { MODKEY,                       XK_s,      setlayout,      {.v = &layouts[3]} },
        { MODKEY,                       XK_h,      setlayout,      {.v = &layouts[4]} },
        { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[5]} },
        { MODKEY,                       XK_space,  setlayout,      {0} },
        { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
        { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
        { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

        { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
        { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

        /* Для мультимедия-клавиатур */
        { 0,                            XF86XK_AudioMedia,      spawn,  {.v = player_prog_cmd } },
        { 0,                            XF86XK_AudioPlay,       spawn,  {.v = player_play_cmd } },
        { 0,                            XF86XK_AudioMute,       spawn,  {.v = audio_mute_cmd } },
        { 0,                            XF86XK_AudioStop,       spawn,  {.v = player_stop_cmd } },
        { 0,                            XF86XK_AudioLowerVolume,spawn,  {.v = audio_lower_cmd} },
//      { MODKEY,                       XF86XK_AudioLowerVolume,spawn,  {.v = front_lower_cmd } },
        { 0,                            XF86XK_AudioRaiseVolume,spawn,  {.v = audio_raise_cmd} },
//      { MODKEY,                       XF86XK_AudioRaiseVolume,spawn,  {.v = front_raise_cmd } },
//      { MODKEY|ShiftMask,             XF86XK_AudioLowerVolume,spawn,  {.v = headphone_l_cmd} },
//      { MODKEY|ShiftMask,             XF86XK_AudioRaiseVolume,spawn,  {.v = headphone_r_cmd} },
        { 0,                            XF86XK_AudioPrev,       spawn,  {.v = player_prev_cmd } },
        { 0,                            XF86XK_AudioNext,       spawn,  {.v = player_next_cmd } },
//      { 0,                            XF86XK_MyComputer,      spawn,  {.v = fileman_cmd } },
//      { 0,                            XF86XK_Favorites,       spawn,  {.v = fileman_cmd } },
//      { 0,                            XF86XK_Search,          spawn,  {.v = browser_cmd } },
//      { 0,                            XF86XK_Mail,            spawn,  {.v = email_cmd   } },
//      { 0,                            XF86XK_Calculator,      spawn,  {.v = calcul_cmd  } },
        /* Регулировка подсветки */
        { 0,                            XF86XK_MonBrightnessUp,  spawn, {.v = xbacklightinc_cmd } },
        { 0,                            XF86XK_MonBrightnessDown,spawn, {.v = xbacklightdec_cmd } },

        TAGKEYS(                        XK_1,                      0)
        TAGKEYS(                        XK_2,                      1)
        TAGKEYS(                        XK_3,                      2)
        TAGKEYS(                        XK_4,                      3)
        TAGKEYS(                        XK_5,                      4)
        TAGKEYS(                        XK_6,                      5)
        TAGKEYS(                        XK_7,                      6)
        TAGKEYS(                        XK_8,                      7)
        TAGKEYS(                        XK_9,                      8)

        { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
        /* click                event mask      button          function        argument */
        { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
        { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
        { ClkWinTitle,          0,              Button2,        zoom,           {0} },
        { ClkStatusText,        0,              Button2,        spawn,          {.v = term_cmd } },
        { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
        { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
        { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
        { ClkTagBar,            0,              Button1,        view,           {0} },
        { ClkTagBar,            0,              Button3,        toggleview,     {0} },
        { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
        { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

