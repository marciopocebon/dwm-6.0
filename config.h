/* See LICENSE file for copyright and license details. */

/* appearance */
static const char           font[]              = "Fira Code:size=10";
static const char           normbordercolor[]   = "#444444";    /* window borders color           */
static const char           normbgcolor[]       = "#1c1c1c";    /* background color               */
static const char           normfgcolor[]       = "#87AFAF";    /* text color in status bar       */
static const char           selbordercolor[]    = "#4271ae";    /* active window border color     */
static const char           selbgcolor[]        = "#262626";    /* window title background color  */
static const char           selfgcolor[]        = "#ffffff";    /* window title color             */
static const unsigned int   borderpx            = 2.5;          /* border pixel of windows        */
static const unsigned int   snap                = 32;           /* snap pixel                     */
static const unsigned int   systrayspacing      = 2;            /* systray spacing                */
static const Bool           showsystray         = True;         /* False means no systray         */
static const Bool           showbar             = True;         /* False means no bar             */
static const Bool           topbar              = False;        /* False means bottom bar         */

/* tagging */
#define MAX_TAGNAME_LEN     14      /* excludes tag number with semicolon */
#define MAX_TAGLEN          16      /* altogether */
#define TAGS                9       /* number of tags */

/* uncomment if you have multiple connected monitors */
//#define MULTIMONS

static char tags[][TAGS][MAX_TAGLEN] = {
#ifdef MULTIMONS
/* monitor 0 */  {"1", "2", "3", "4", "5", "6", "7", "8", "9:gmb"},
/* monitor 1 */  {"1", "2:mail", "3:chat", "4", "5", "6", "7", "8", "9:qb"},
/*    ...    */
#else
                 {"1:ff", "2:tb", "3", "4", "5", "6", "7", "8:qb", "9:gmb" },
#endif
};

static const Rule rules[] = {
/* class                instance        title           role            tags mask       isfloating      monitor */

 { "Gmusicbrowser.pl",  "gmusicbrowser.pl", NULL,       NULL,           256,            False,          0 },
 { "Gmusicbrowser.pl",  "gmusicbrowser.pl","Equalizer", "Equalizer",    256,            True,           0 },

#ifdef MULTIMONS
 /* Don't forget to install window_merge plugin */
 { "Pidgin",            NULL,           NULL,           "buddy_list",   4,              False,          1  },
 { "Thunderbird",       NULL,           NULL,           NULL,           2,              False,          1  },
 { "qBittorrent",       "qbittorrent",  NULL,           NULL,           256,            False,          1  },
#else
/***********************************************************************************************************/
 { "Firefox",           NULL,           NULL,           NULL,           0,              False,          0  },
 { "Pidgin",            NULL,           NULL,           "buddy_list",   2,              False,          0  },
 { "Thunderbird",       NULL,           NULL,           NULL,           2,              False,          0  },
 { "qBittorrent",       "qbittorrent",  NULL,           NULL,           128,            False,          0  },
/***********************************************************************************************************/
#endif

 /* current active monitor */
 { "Gimp",              NULL,           NULL,           NULL,           0,              True,           -1 },
 { "Lazarus",           NULL,           NULL,           NULL,           0,              True,           -1 },
 { "floaterm",          "xterm",        NULL,           NULL,           0,              True,           -1 },
 { "XBiff",             "xbiff",        "xbiff",        NULL,           ~0,             True,           -1 },
 { "XClock",            "xclock",       "xclock",       NULL,           ~0,             True,           -1 },
 { "XCalc",             "xcalc",        "Calculator",   NULL,           0,              True,           -1 },
 { "Xmessage",          "xmessage",     "xmessage",     NULL,           0,              True,           -1 },
 { "Ssvnc.tcl",         "ssvnc.tcl",    "SSL/SSH VNC Viewer", NULL,     0,              True,           -1 },
};

/* layout(s) */
static const float  mfact       = 0.55;     /* factor of master area size [0.05..0.95] */
static const int    nmaster     = 1;        /* number of clients in master area */
static const Bool   resizehints = False;    /* True means respect size hints in tiled resizals */

#include "bstack.c"
#include "bstackhoriz.c"
#include "gaplessgrid.c"
static const Layout layouts[] = {
        /* symbol     arrange function */
        { "[]=",      tile },               /* first entry is default */
        { "><>",      NULL },               /* no layout function means floating behavior */
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

/* Multimedia keyboard definitions */
#include <X11/XF86keysym.h>

/* Change current tag name. Called by MODKEY + n */
#define ROFI_CMD_CHANGE_TAG \
	"rofi -dmenu -p 'Set current tag name' -width 20 -lines 0"
static const char *rofi_cmd[] = { "rofi", "-combi-modi", "drun,run", "-show", "combi", "-modi", "combi", NULL };
//static const char *rofi_cmd[] = { "rofi", "-show", "drun", "-modi", "drun,run", NULL };
static const char *lock_cmd[] = { "trollock", NULL };
static const char *term_cmd[] = { "urxvtc",   NULL };

/* Gmusicbrowser settings */
static const char *player_prog_cmd[]    = { "gmusicbrowser",                                NULL };
static const char *player_stop_cmd[]    = { "gmusicbrowser", "-cmd", "Stop",                NULL };
static const char *player_play_cmd[]    = { "gmusicbrowser", "-cmd", "PlayPause",           NULL };
static const char *player_prev_cmd[]    = { "gmusicbrowser", "-cmd", "PrevSongInPlaylist",  NULL };
static const char *player_next_cmd[]    = { "gmusicbrowser", "-cmd", "NextSongInPlaylist",  NULL };
static const char *player_mute_cmd[]    = { "gmusicbrowser", "-cmd", "TogMute",             NULL };
static const char *player_incv_cmd[]    = { "gmusicbrowser", "-cmd", "IncVolume",           NULL };
static const char *player_decv_cmd[]    = { "gmusicbrowser", "-cmd", "DecVolume",           NULL };
/*
static const char *player_quit_cmd[]    = { "gmusicbrowser", "-cmd", "Quit",                NULL };
*/

/* ALSA settings */
/*
static const char *master_mute_cmd[]    = { "amixer", "sset", "Master",     "toggle",   NULL };
static const char *master_decv_cmd[]    = { "amixer", "sset", "Master",     "1-",       NULL };
static const char *master_incv_cmd[]    = { "amixer", "sset", "Master",     "1+",       NULL };

static const char *front_mute_cmd[]     = { "amixer", "sset", "Front",      "toggle",   NULL };
static const char *front_decv_cmd[]     = { "amixer", "sset", "Front",      "1-",       NULL };
static const char *front_incv_cmd[]     = { "amixer", "sset", "Front",      "1+",       NULL };

static const char *headphone_mute_cmd[] = { "amixer", "sset", "Headphone",  "toggle",   NULL };
static const char *headphone_decv_cmd[] = { "amixer", "sset", "Headphone",  "1-",       NULL };
static const char *headphone_incv_cmd[] = { "amixer", "sset", "Headphone",  "1+",       NULL };
*/

/* Notebooks settings */
static const char *xbacklight_i_cmd[]   = { "xbacklight", "-inc", "10", NULL };
static const char *xbacklight_d_cmd[]   = { "xbacklight", "-dec", "10", NULL };

/*************************************************************************************/

static Key keys[] = {
        /* modifier                     key                             function        argument */
        { MODKEY,                       XK_p,                           spawn,          {.v = rofi_cmd } },
        { MODKEY,                       XK_l,                           spawn,          {.v = lock_cmd } },
        { MODKEY|ShiftMask,             XK_Return,                      spawn,          {.v = term_cmd } },
        { MODKEY,                       XK_b,                           togglebar,      {0} },

        { MODKEY,                       XK_n,                           nametag,        {0} },

        { MODKEY,                       XK_Up,                          focusstack,     {.i = +1 } },
        { MODKEY,                       XK_Down,                        focusstack,     {.i = -1 } },

        { MODKEY,                       XK_F1,                          focusnstack,    {.i = 1 } },
        { MODKEY,                       XK_F2,                          focusnstack,    {.i = 2 } },
        { MODKEY,                       XK_F3,                          focusnstack,    {.i = 3 } },
        { MODKEY,                       XK_F4,                          focusnstack,    {.i = 4 } },
        { MODKEY,                       XK_F5,                          focusnstack,    {.i = 5 } },
        { MODKEY,                       XK_F6,                          focusnstack,    {.i = 6 } },
        { MODKEY,                       XK_F7,                          focusnstack,    {.i = 7 } },
        { MODKEY,                       XK_F8,                          focusnstack,    {.i = 8 } },
        { MODKEY,                       XK_F9,                          focusnstack,    {.i = 9 } },

        { MODKEY,                       XK_i,                           incnmaster,     {.i = +1 } },
        { MODKEY,                       XK_d,                           incnmaster,     {.i = -1 } },
        { MODKEY|ShiftMask,             XK_Left,                        setmfact,       {.f = -0.05} },
        { MODKEY|ShiftMask,             XK_Right,                       setmfact,       {.f = +0.05} },

        { MODKEY,                       XK_Return,                      zoom,           {0} },
        { MODKEY,                       XK_Tab,                         view,           {0} },
        { MODKEY,                       XK_c,                           killclient,     {0} },
        { MODKEY,                       XK_t,                           setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       XK_f,                           setlayout,      {.v = &layouts[1]} },
        { MODKEY,                       XK_m,                           setlayout,      {.v = &layouts[2]} },
        { MODKEY,                       XK_s,                           setlayout,      {.v = &layouts[3]} },
        { MODKEY,                       XK_h,                           setlayout,      {.v = &layouts[4]} },
        { MODKEY,                       XK_g,                           setlayout,      {.v = &layouts[5]} },
        { MODKEY,                       XK_space,                       setlayout,      {0} },
        { MODKEY|ShiftMask,             XK_space,                       togglefloating, {0} },
        { MODKEY,                       XK_0,                           view,           {.ui = ~0 } },
        { MODKEY|ShiftMask,             XK_0,                           tag,            {.ui = ~0 } },

        { MODKEY,                       XK_comma,                       focusmon,       {.i = -1 } },
        { MODKEY,                       XK_period,                      focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,             XK_comma,                       tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,             XK_period,                      tagmon,         {.i = +1 } },

        TAGKEYS(                        XK_1,                      0)
        TAGKEYS(                        XK_2,                      1)
        TAGKEYS(                        XK_3,                      2)
        TAGKEYS(                        XK_4,                      3)
        TAGKEYS(                        XK_5,                      4)
        TAGKEYS(                        XK_6,                      5)
        TAGKEYS(                        XK_7,                      6)
        TAGKEYS(                        XK_8,                      7)
        TAGKEYS(                        XK_9,                      8)

        { MODKEY|ShiftMask,             XK_q,                           quit,           {0} },

        /*********************************
         * Multimedia keyboard shortcuts *
         *********************************/

        /* Gmusicbrowser */
        { 0,                            XF86XK_AudioMedia,              spawn,  {.v = player_prog_cmd } },
        { 0,                            XF86XK_AudioPlay,               spawn,  {.v = player_play_cmd } },
        { 0,                            XF86XK_AudioStop,               spawn,  {.v = player_stop_cmd } },
        { 0,                            XF86XK_AudioMute,               spawn,  {.v = player_mute_cmd } },
        { 0,                            XF86XK_AudioPrev,               spawn,  {.v = player_prev_cmd } },
        { 0,                            XF86XK_AudioNext,               spawn,  {.v = player_next_cmd } },
        { 0,                            XF86XK_AudioLowerVolume,        spawn,  {.v = player_decv_cmd } },
        { 0,                            XF86XK_AudioRaiseVolume,        spawn,  {.v = player_incv_cmd } },

        /* ALSA */
//      { 0,                            XF86XK_AudioMute,               spawn,  {.v = master_mute_cmd } },
//      { 0,                            XF86XK_AudioLowerVolume,        spawn,  {.v = master_decv_cmd } },
//      { 0,                            XF86XK_AudioRaiseVolume,        spawn,  {.v = master_incv_cmd } },
//      { ShiftMask,                    XF86XK_AudioMute,               spawn,  {.v = front_mute_cmd } },
//      { ShiftMask,                    XF86XK_AudioLowerVolume,        spawn,  {.v = front_decv_cmd } },
//      { ShiftMask,                    XF86XK_AudioRaiseVolume,        spawn,  {.v = front_incv_cmd } },
//      { MODKEY|ShiftMask,             XF86XK_AudioMute,               spawn,  {.v = headphone_mute_cmd } },
//      { MODKEY|ShiftMask,             XF86XK_AudioLowerVolume,        spawn,  {.v = headphone_decv_cmd } },
//      { MODKEY|ShiftMask,             XF86XK_AudioRaiseVolume,        spawn,  {.v = headphone_incv_cmd } },

//      { 0,                            XF86XK_Mail,                    spawn,  {.v = mailclient_cmd } },
//      { 0,                            XF86XK_Calculator,              spawn,  {.v = calculator_cmd } },


        /* Brightness */
        { 0,                            XF86XK_MonBrightnessUp,         spawn,  {.v = xbacklight_i_cmd } },
        { 0,                            XF86XK_MonBrightnessDown,       spawn,  {.v = xbacklight_d_cmd } },

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

/* End of file */
