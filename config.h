/* See LICENSE file for copyright and license details. */
/* Compile with: # make clean install */
// For multimedia keys
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[] = {
                 "Hack:pixelsize=12:antialias=true:hinting=true",
                 "mononoki Nerd Font:pixelsize=12:antialias=true:hinting=true",
                 "FontAwesome:pixelsize=12:antialias=true", };
static const char dmenufont[]       = "Hack:pixelsize=12:antialias=true_hinting=true";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_high[]        = "#397b88";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray2, col_high  },
};

/* tagging */
//static const char *tags[] = { "1", "2", "3", "4", "5", "6" };
static const char *tags[] = { "", "", "", "", "", "" };

/* To open in first tag 1, for 2: 1<<1, for 3: 1<<2, etc. */
static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "firefox",  NULL,       NULL,       1,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow = 1; /* 1 means attach after the current active window */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
    { "ﳶ",      bstack },   /* first entry is default */
	{ "",      tile },
	{ "",      monocle },
	{ "",      NULL },     /* floating */
    //{ "充",      bstack },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_gray1, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "urxvt", NULL };
static const char *browser[] = { "firefox", NULL };
static const char *files[] = { "thunar", NULL };
static const char *changebg[] = { "/usr/bin/feh", "--randomize", "--bg-fill", "~/Utilidades/Wallpapers/*", NULL };
static const char *ayuda[] = { "/usr/local/bin/ayuda", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ ControlMask,                  XK_space,  spawn,          {.v = dmenucmd } },
	{ Mod1Mask,                     XK_space,  spawn,          {.v = termcmd } },
	{ 0,                    XF86XK_AudioMute,  spawn,          SHCMD("pamixer -t; kill -41 $(pidof dwmblocks)") },
	{ 0,             XF86XK_AudioRaiseVolume,  spawn,         SHCMD("pamixer -i 3; kill -41 $(pidof dwmblocks)") },
	{ 0,             XF86XK_AudioLowerVolume,  spawn,         SHCMD("pamixer -d 3; kill -41 $(pidof dwmblocks)") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_j,      setcfact,       {.f = -0.25} },
	{ MODKEY|ControlMask,           XK_k,      setcfact,       {.f = +0.25} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_x,      killclient,     {0} },
	{ MODKEY,                       XK_h,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_f,      togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	//{ MODKEY|ShiftMask,             XK_o,      rotatestack,    {.i = -1 } },
	//{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	//{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	//{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	//{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|Mod1Mask,              XK_i,      spawn,          {.v = browser } },
	{ MODKEY|Mod1Mask,              XK_b,      spawn,          {.v = changebg } },
    { MODKEY,                       XK_space,  spawn,          {.v = files } },
    { MODKEY|Mod1Mask,              XK_h,      spawn,          {.v = ayuda } },
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

