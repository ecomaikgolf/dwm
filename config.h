/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=11" };
static const char dmenufont[]       = "monospace:size=13";

static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";

static char *colors[][3] = {
        /*               fg           bg           border   */
        [SchemeNorm] = { "#8ec07c", "#282828", "#000000"},
        [SchemeSel]  = { "#d65d0e",  "#282828",  "#d65d03" },
	[SchemeStatus]  = { "#fbf1c7", "#282828",  "#000000"  }, 
	[SchemeTagsSel]  = { "#000000", "#d65d03",  "#000000"  },
        [SchemeTagsNorm]  = { "#000000", "#8ec07c",  "#000000"  },
        [SchemeInfoSel]  = { "#fb1f1c", "#282828",  "#000000"  }, 
        [SchemeInfoNorm]  = { "#000000", "#282828",  "#000000"  }
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "T",      tile },    /* first entry is default */
	{ "F",      NULL },    /* no layout function means floating behavior */
	{ "M",      monocle },
        { "G",       grid},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ KeyPress,   MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ KeyPress,   MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ KeyPress,   MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ KeyPress,   MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* vim-like stack management */
#define STACKKEYS(MOD,ACTION) \
        { KeyPress, MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
        { KeyPress, MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0";
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
        /* Manage the stack */
        STACKKEYS(MODKEY,           focus)
        STACKKEYS(MODKEY|ShiftMask, push)

        /* Spawn terminals */
	{ KeyPress,   MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ KeyPress,   MODKEY|ShiftMask,             XK_Return, togglescratch,  {.v = scratchpadcmd} },

        /* Fullscreen */
	{ KeyPress,   MODKEY,                       XK_f,      togglefullscr,  {0} },

        /* Go-to last tag */
	{ KeyPress,   MODKEY,                       XK_Tab,    view,           {0} },

        /* Kill client */
	{ KeyPress,   MODKEY,                       XK_q,      killclient,     {0} },

        /* Layouts (tabbed & grid only) */
	{ KeyPress,   MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ KeyPress,   MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
        
        /* Floating */
	{ KeyPress,   MODKEY,                       XK_space,  togglefloating, {0} },

        /* Tags */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ KeyPress,   MODKEY,           XK_0,      view,           {.ui = ~0 } },

        /* Software */
	{ KeyPress, MODKEY,			XK_c,		spawn,		SHCMD("brave") },
	{ KeyPress, MODKEY,       		XK_w,		spawn,		SHCMD("whatsapp-nativefier") },
        { KeyPress, MODKEY,			XK_d,		spawn,          SHCMD("rofi -show run") },
	{ KeyPress, MODKEY,			XK_r,		spawn,		SHCMD("st -e lf") },
	{ KeyPress, MODKEY,			XK_s,		spawn,		SHCMD("signal-desktop") },
        { KeyRelease , MODKEY,			XK_i,		spawn,		SHCMD("setsid selscrot &") },
	{ KeyPress, MODKEY|ShiftMask,		XK_l,		spawn,		SHCMD("slock") },
	{ KeyPress, MODKEY,           		XK_e,		spawn,		SHCMD("electron-mail") },
	{ KeyPress, MODKEY,           		XK_p,		spawn,		SHCMD("rofi-pass") },

        /* Audio */
        { KeyPress,0,                           XF86XK_AudioMute,		spawn,		SHCMD("pactl set-sink-mute alsa_output.pci-0000_00_1b.0.analog-stereo toggle") },
        { KeyPress,0,                           XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pactl set-sink-volume alsa_output.pci-0000_00_1b.0.analog-stereo +5%") },
        { KeyPress,0,                           XF86XK_AudioLowerVolume,	spawn,		SHCMD("pactl set-sink-volume alsa_output.pci-0000_00_1b.0.analog-stereo -5%") },

        { KeyPress,0,                           XF86XK_AudioPrev,		spawn,		SHCMD("playerctl previous") },
        { KeyPress,0,                           XF86XK_AudioNext,		spawn,		SHCMD("playerctl next") },
        { KeyPress,0,                           XF86XK_AudioPause,		spawn,		SHCMD("playerctl pause") },
        { KeyPress,0,                           XF86XK_AudioPlay,		spawn,		SHCMD("playerctl play") },
        { KeyPress,0,                           XF86XK_AudioStop,		spawn,		SHCMD("playerctl stop") },

        /* Brillo */
        { KeyPress,0,                           XF86XK_MonBrightnessUp,		spawn,		SHCMD("lumeus +10%") },
        { KeyPress, 0,                          XF86XK_MonBrightnessDown,       spawn,		SHCMD("lumeus -10%") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

