/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappx     = 4;        /* gaps between windows */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 20;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "Symbols Nerd Font Mono:size=11", "JetBrainsMono NF SemiBold:size=11"};
static const char dmenufont[]       = "monospace:size=12";
static const char col_gray1[]       = "#1d2021";
static const char col_gray2[]       = "#A66946";
static const char col_gray3[]       = "#D99B66";
static const char col_gray4[]       = "#D9B166";
static const char col_blue[]        = "#593E2E";
static const char border_active[]   = "#BF4B21";
static const char border_normal[]   = "#3E4C59";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray2, col_gray1,  border_normal},
	[SchemeSel]  = { col_gray1, col_gray4,  border_active},
};

/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */
static const char *tags[] = { " 󱇙 ", "󰖟" , "", "", "", "", "" , "" , ""};

/* Lockfile */
static char lockfile[] = "/tmp/dwm.lock";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     switchtotag    iscentered   isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,                0,            0,           1,           -1 },
	{ "firefox",  NULL,       NULL,       1 << 1,           1,            0,           0,           -1 },
    { "firefox",  "Toolkit",  "Picture-in-Picture", 0,      0,            0,           1,           -1 },
    { "firefox",  "Library",  "Library",  0,                0,            1,           1,           -1 },
	{ "krita",    NULL,       NULL,       1 << 2,           1,            0,           0,           -1 },
    { "OpenToonz",NULL,       NULL,       1 << 2,           1,            0,           0,           -1 },
	{ "mpv",      NULL,       NULL,       1 << 4,           1,            0,           0,           -1 },
	{ "Thunar",   NULL,       NULL,       1 << 5,           1,            0,           0,           -1 },
    { "Emacs",    NULL,       NULL,       1 << 3,           1,            0,           0,           -1 },
	{ "copyq",    NULL,       NULL,       0,                0,            1,           1,           -1 },
	{ "qBittorrent",    NULL, NULL,       1 << 8,           1,            0,           0,           -1 },
	{ "feh",      NULL,       NULL,       0,                0,            1,           1,           -1 },

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL},    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define Altkey Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#include "movestack.c"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_blue, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *browser[]  = {"firefox", NULL};
static const char *fileBrowser[] = {"Thunar", NULL};
static const char *krita[]  = {"krita", NULL};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ Altkey,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,			            XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,      togglebar,      {0} },
	{ Altkey,                       XK_j,      focusstack,     {.i = +1 } },
	{ Altkey,                       XK_k,      focusstack,     {.i = -1 } },
	{ Altkey|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ Altkey|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,      zoom,           {0} },
	{ MODKEY,                       XK_Escape, view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      fullscreen,     {0}},
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ Altkey|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
    { MODKEY,                       XK_b,      spawn,          {.v = browser}},
    { MODKEY|ShiftMask,             XK_period, spawn,          {.v = krita}},
    { MODKEY,                       XK_e,      spawn,          {.v = fileBrowser}},
    { MODKEY|ShiftMask,             XK_comma,  spawn,          SHCMD("opentoonz")},
    { MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD("wallpaper random")},
    { MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("wallpaper show")},
    { MODKEY|ShiftMask,             XK_x,      spawn,          SHCMD("systemctl --user restart xppentablet.service")},
    { MODKEY|ShiftMask,             XK_i,      spawn,          SHCMD("firefox --private-window")},
    { MODKEY,                       XK_bracketright, spawn,    SHCMD("amixer set Master 5%+")},
    { MODKEY,                       XK_bracketleft, spawn,     SHCMD("amixer set Master 5%-")},
    { MODKEY,                       XK_backslash, spawn,       SHCMD("amixer set Master toggle")},
    { MODKEY|ControlMask,           XK_l,      spawn,          SHCMD("betterlockscreen -l")},
    { MODKEY|ShiftMask,             XK_minus,  spawn,          SHCMD("betterlockscreen -s")},
    { MODKEY,                       XK_a,      spawn,          SHCMD("copyq toggle")},
    { MODKEY,                       XK_o,      spawn,          SHCMD("emacsclient -c")},
    { MODKEY,                       XK_semicolon, spawn,       SHCMD("changebrightness up")},
    { MODKEY|ShiftMask,             XK_semicolon, spawn,       SHCMD("changebrightness down")},
    { 0,                             XK_Print,  spawn,         SHCMD("scrot ~/Pictures/Screenshots/%b%d::%H%M%S.png --focused -b && notify-send 'Screenshot taken' 'Saved in ~/Pictures/Screenshots' || exit")},
    { ShiftMask,                    XK_Print,  spawn,          SHCMD("scrot ~/Pictures/Screenshots/%b%d::%H%M%S.png --select --line mode=edge && notify-send 'Screenshot taken' 'Saved in ~/Pictures/Screenshots' || exit")},
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
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
