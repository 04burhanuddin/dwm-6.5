/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;  /* border pixel of windows */
static const unsigned int gappx     = 4;  /* gaps between windows */
static const unsigned int snap      = 32; /* snap pixel */
static const int swallowfloating    = 0;  /* 1 means swallow floating windows by default */
static const int showbar            = 1;  /* 0 means no bar */
static const int topbar             = 1;  /* 0 means bottom bar */
static const char *fonts[]          = {"JetbrainsMono Nerd Font:size=11:antialias=true:autohint=true", "MesloLGS NF:pixelsize=11:antialias=true:autohint=true"};
static const char dmenufont[]       = "JetbrainsMono Nerd Font:size=11:antialias=true:autohint=true";

/* Default color */
/*static char normbgcolor[]     = "#222222";
static char normbordercolor[]   = "#444444";
static char normfgcolor[]       = "#bbbbbb";
static char selfgcolor[]        = "#eeeeee";
static char selbordercolor[]    = "#005577";
static char selbgcolor[]        = "#005577";*/

/* Everforest dark */
static char normbgcolor[]       = "#222222";
static char normbordercolor[]   = "#475258";
static char normfgcolor[]       = "#BDDABB";
static char selfgcolor[]        = "#000000";
static char selbordercolor[]    = "#7A8478";
static char selbgcolor[]        = "#A7C080";

static char *colors[][3] = {
  /*                  fg              bg            border   */ 
  [SchemeNorm]      = { normfgcolor,  normbgcolor,  normbordercolor },
  [SchemeSel]       = { selfgcolor,   selbgcolor,   selbordercolor },
  [SchemeStatus]    = { normfgcolor,  normbgcolor,  "#000000" }, // Statusbar right {text,background,not used but cannot be empty}
  [SchemeTagsSel]   = { selfgcolor,   selbgcolor,   "#000000" }, // Tagbar left selected {text,background,not used but cannot be empty}
  [SchemeTagsNorm]  = { normfgcolor,  normbgcolor,  "#000000" }, // Tagbar left unselected {text,background,not used but cannot be empty}
  [SchemeInfoSel]   = { selfgcolor,   selbgcolor,   "#000000" }, // infobar middle  selected {text,background,not used but cannot be empty}
  [SchemeInfoNorm]  = { normfgcolor,  selbgcolor,   "#000000" }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* brightness */
static const char *brighter[] = { "brightnessctl", "set", "5%+", NULL };
static const char *dimmer[]   = { "brightnessctl", "set", "5%-", NULL };

/* volume */
static const char *up_vol[]   = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%",   NULL };
static const char *down_vol[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%",   NULL };
static const char *mute_vol[] = { "pactl", "set-sink-mute",   "@DEFAULT_SINK@", "toggle", NULL };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance  title           tags mask   isfloating  isterminal  noswallow   monitor */
  { "obs",            NULL,     NULL,           0,          1,          0,          0,          -1 },
  { "code",           NULL,     NULL,           0,          1,          0,          0,          -1 },
  { "vlc",            NULL,     NULL,           0,          1,          0,          0,          -1 },
  { "st",             NULL,     NULL,           0,          1,          1,          0,          -1 },
  { "Google-chrome",  NULL,     NULL,           0,          1,          0,          0,          -1 },
  { "pavucontrol",    NULL,     NULL,           0,          1,          0,          0,          -1 },
  { "Lxappearance",   NULL,     NULL,           0,          1,          0,          0,          -1 },
  { NULL,             NULL,     "Event Tester", 0,          0,          0,          1,          -1 }, /* xev */

};

/* layout(s) */
static const float mfact        = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
  { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont };
static const char *termcmd[]  = { "st", NULL };

#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
  { MODKEY|ControlMask,           XK_comma,  cyclelayout,    {.i = -1 } },
  { MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
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
  { MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
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
  { 0, XF86XK_MonBrightnessDown,  spawn, {.v = dimmer } },
  { 0, XF86XK_MonBrightnessUp,    spawn, {.v = brighter } },
  { 0, XF86XK_AudioMute,          spawn, {.v = mute_vol } },
  { 0, XF86XK_AudioLowerVolume,   spawn, {.v = down_vol } },
  { 0, XF86XK_AudioRaiseVolume,   spawn, {.v = up_vol } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
