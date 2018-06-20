/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "xos4 Terminus:pixelsize=14", "monospace:size=10" };
static const char font[]            = "xos4 Terminus:pixelsize=14";
static const char dmenufont[]       = "xos4 Terminus:pixelsize=14";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#cccccc";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#99ccff";
static const char col_darkred[]     = "#551111";
static const char col_litered[]     = "#cc5555";
static const char *colors[][4]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2, col_darkred },
	[SchemeSel]  = { col_gray4, col_gray2, col_cyan, col_litered  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "w", "l", "c", "+" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1,          0 },
  { "URxvt",    NULL,       "logs",     1 << 9,       0,           -1,          0 },
  { "Xchat",    NULL,       NULL,       1 << 10,      0,           -1,          0 },
  { "KeePass2", NULL,       NULL,       1 << 11,      0,           -1,          0 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};



/* key definitions */
/* key definitions */
#define ctrl			ControlMask
#define alt			  Mod1Mask
#define shift			ShiftMask
#define MODKEY Mod1Mask

#define TAGKEYS(KEY,TAG) \
	{ alt,                          KEY,      view,           {.ui = 1 << TAG} }, \
	{ ctrl|alt,                     KEY,      tag,     {.ui = 1 << TAG} }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_gray2, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "urxvt", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
  { alt,                          XK_p,      spawn,          {.v = dmenucmd}},
  { ctrl,                         XK_Return, spawn,          {.v = termcmd}},
	{ alt,                          XK_b,      togglebar,      {0} },

	{ alt,                          XK_Up,     focusstack,     {.i = +1 } },
	{ alt,                          XK_Down,   focusstack,     {.i = -1 } },
	{ alt,                          XK_Left,   setmfact,       {.f = -0.05} },
	{ alt,                          XK_Right,  setmfact,       {.f = +0.05} },
	{ ctrl,                         XK_Up,     incnmaster,     {.i = +1 } },
	{ ctrl,                         XK_Down,   incnmaster,     {.i = -1 } },

	{ alt,                          XK_z,      zoom,           {0} },
	{ alt,                          XK_grave,  view,           {0} },
	{ ctrl|alt,                     XK_c,      killclient,     {0} },

	{ ctrl|alt,                     XK_Left,   setlayout,      {.v = &layouts[0]}},
	{ ctrl|alt,                     XK_Down,   setlayout,      {.v = &layouts[1]}},
	{ ctrl|alt,                     XK_Right,  setlayout,      {.v = &layouts[2]}},
	{ ctrl|alt,                     XK_space,  togglefloating, {0}},

	{ alt,                          XK_comma,  focusmon,       {.i = -1 } },
	{ alt,                          XK_period, focusmon,       {.i = +1 } },
	{ ctrl|alt,                     XK_comma,  tagmon,         {.i = -1 } },
	{ ctrl|alt,                     XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,      0)
	TAGKEYS(                        XK_2,      1)
	TAGKEYS(                        XK_3,      2)
	TAGKEYS(                        XK_4,      3)
	TAGKEYS(                        XK_5,      4)
	TAGKEYS(                        XK_6,      5)
	TAGKEYS(                        XK_7,      6)
	TAGKEYS(                        XK_8,      7)
	TAGKEYS(                        XK_9,      8)
	TAGKEYS(                        XK_0,      9)
	TAGKEYS(                        XK_minus,  10)
	TAGKEYS(                        XK_equal,  11)
	{ ctrl|alt,                     XK_q,      quit,           {0} },
	{ ctrl|shift,                   XK_q,      quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
  //{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  //{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  //{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
  //{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         alt,            Button1,        movemouse,      {0} },
	{ ClkClientWin,         alt,            Button2,        togglefloating, {0} },
	{ ClkClientWin,         alt,            Button3,        resizemouse,    {0} },
  //{ ClkTagBar,            0,              Button1,        view,           {0} },
  //{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
  //{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  //{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

