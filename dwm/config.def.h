/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_wincyan[]        = "#087BD3";
static const char col_magenta[]     = "#ff00ff";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	//[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeSel]  = { col_gray4, col_cyan,  col_magenta  },
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
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
 	{ "[@]",      spiral }, /* first entry is default */
	{ "[]=",      tile },    
	{ "[M]",      monocle }, // FULLSCREEN NEEDS monocle on N°2
	{ "><>",      NULL },    /* no layout function means floating behavior */
 	{ "[\\]",     dwindle },
};

/* key definitions */
#define MODKEY Mod4Mask // Mod4Mask -> SUPER Mod1Mask -> ALT
#define NONE 0
#define TAGKEYS(KEY,TAG) \
	{ Mod1Mask,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ Mod1Mask|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
    


/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
//     { Mod1Mask,                       KEY,      focusnthmon,    {.i  = TAG } },
/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *shutdowncmd[] = {"sudo", "/sbin/systemctl", "poweroff", NULL };
static const char *rebootcmd[] = {"sudo", "/sbin/systemctl", "reboot", NULL };
static const char *filemanagercmd[] = {"thunar", NULL };
static const char *firefoxcmd[] = {"firefox", NULL };
static const char *xfce4term[] = {"xfce4-terminal", NULL };
static const char *connectHeadset[] = {"/home/lean/headsetConnect.sh", NULL };
//static const char *increaseVOL[] = {"wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "5%+", NULL };
//static const char *decreaseVOL[] = {"wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "5%-", NULL };
static const char *increaseVOL[] = {"/home/lean/scripts/Volume.sh", "--inc", NULL };
static const char *decreaseVOL[] = {"/home/lean/scripts/Volume.sh", "--dec", NULL };
static const char *playpause[] = {"playerctl","play-pause", NULL };
static const char *flameshotcmd[] = {"flameshot", "gui", NULL };
static const char *startWindows[] = {"/home/lean/win10VM.sh", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ NONE,				XK_Print, 	 spawn, 	  {.v = flameshotcmd} },
	{ NONE,           0x1008ff13,    spawn,       {.v = increaseVOL } }, //RAISE
	{ NONE,           0x1008ff14,    spawn,       {.v = playpause } }, //PLAY	(play)
	{ NONE,           0x1008ff31,    spawn,       {.v = playpause } }, //PLAY	(pause)
	{ NONE,           0x1008ff11,    spawn,       {.v = decreaseVOL } }, //LOWER
	{ MODKEY,           XK_bar,    spawn,       {.v = connectHeadset } },
	{ MODKEY,			XK_F1,     spawn,	   {.v = shutdowncmd } }, //hypr
	{ MODKEY,			XK_F2,     spawn,	   {.v = rebootcmd } }, //hypr
	{ MODKEY,			XK_F10,    spawn, 		{.v = startWindows} },
	{ MODKEY,             		XK_q, 	   spawn,          {.v = xfce4term  } }, //hypr 'st'
	{ MODKEY|ShiftMask,             XK_q, 	   spawn,          {.v = termcmd } }, //hypr 'xfce4-terminal'
	{ MODKEY,           		XK_c,      killclient,     {0} },  //hypr
	{ MODKEY,                       XK_t,      spawn,          {.v = filemanagercmd } }, //thunar
	{ MODKEY,                       XK_v,      togglefloating, {0} }, // hypr
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } }, //hypr
	{ MODKEY,			XK_e,      spawn,	   {.v = firefoxcmd } },//fire
	{ MODKEY,             XK_f,      fullscreen,     {0} }, //fullscreen
	{ MODKEY,                       XK_w,      togglebar,      {0} },	//hypr
																		//shift + w -> toggle-bar-size(normal-thin)
	{ MODKEY,                       XK_Down,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Up,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_Left,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_Right,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ Mod1Mask,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },

	//{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	//{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	//{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	
	{ MODKEY,  						XK_z, 	   swapmon, 		{.i = 30} },

	{ MODKEY,                       XK_1,      focusnthmon,    {.i  = 3 } }, //SONY (L)
	{ MODKEY,                       XK_2,      focusnthmon,    {.i  = 2 } }, //LG (UP)
	{ MODKEY,                       XK_3,      focusnthmon,    {.i  = 0 } }, //PHILPS (M)
	{ MODKEY,                       XK_4,      focusnthmon,    {.i  = 1 } }, //SAMSUNG (R)
	
	{ MODKEY|ShiftMask,             XK_1,      tagnthmon,      {.i  = 3 } }, //SONY (L)
	{ MODKEY|ShiftMask,             XK_2,      tagnthmon,      {.i  = 2 } }, //LG (UP)
	{ MODKEY|ShiftMask,             XK_3,      tagnthmon,      {.i  = 0 } }, //PHILPS (M)
	{ MODKEY|ShiftMask,             XK_4,      tagnthmon,      {.i  = 1 } }, //SAMSUNG (R)
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_m,      quit,           {0} }, //hypr + shift
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

