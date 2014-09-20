/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "Dejavu Sans 8";
static const char normbordercolor[] = "#000000";
static const char normbgcolor[]     = "#000000";
static const char normfgcolor[]     = "#ffffff";
static const char selbordercolor[]  = "#f9785b";
static const char selbgcolor[]      = "#33916d";
static const char selfgcolor[]      = "#ffffff";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const Bool extrabar          = True;     /* False means no extra bar */
static const Bool statusmarkup      = True;     /* True means use pango markup in status message */

/* tagging */
static const char *tags[] = { "term", "web", "games", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ NULL,       NULL,       NULL,       0,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      tag,            {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "run-recent.sh", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvt", "-tr", "-sh", "15", NULL };
static const char *AudioPrev[] = { "music_control.sh", "-c", "prev", NULL }; 
static const char *AudioPlay[] = { "music_toggle.sh", NULL }; 
static const char *AudioNext[] = { "music_control.sh", "-c", "next", NULL }; 
static const char *AudioPauseAfterNext[] = { "music_control.sh", "-c", "one_single", NULL }; 
static const char *MusicLowerVolume[] = { "mpc", "-q", "volume", "-5", NULL }; 
static const char *AudioLowerVolume[] = { "amixer", "set", "Master", "5%-", NULL }; 
static const char *MusicRaiseVolume[] = { "mpc", "-q", "volume", "+5", NULL }; 
static const char *AudioRaiseVolume[] = { "amixer", "set", "Master", "5%+", NULL }; 
static const char *AudioMute[] = { "amixer", "set", "Master", "toggle", NULL }; 
static const char *TouchpadToggle[] = { "touchpad-toggle.sh", NULL };
static const char *LockScreen[] = { "i3lock_with_bg.sh", NULL };
static const char *Mouse[] = {"iocane", "-i", NULL };
static const char *ChBg[] = { "changebg.sh", NULL };
static const char *BlankWin[] = { "blank_window.sh", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_b,      toggleextrabar, {0} },
	{ MODKEY|ShiftMask,             XK_b,      toggleextrabar, {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_comma,  incnmaster,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_period, incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = 1.50} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} }, 
    { MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
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

        /* Multimedia Keys */
        { 0,                            0x1008ff16,spawn,          {.v = AudioPrev } },
        { ControlMask,                  XK_F8,     spawn,          {.v = AudioPrev } },
        { 0,                            0x1008ff14,spawn,          {.v = AudioPlay } },
        { ControlMask,                  XK_F9,     spawn,          {.v = AudioPlay } },
        { 0,                            0x1008ff17,spawn,          {.v = AudioNext } },
        { ControlMask,                  XK_F10,    spawn,          {.v = AudioNext } },
        { MODKEY,                       XK_F9,     spawn,          {.v = AudioPauseAfterNext } },
        { 0,                            0x1008ff11,spawn,          {.v = AudioLowerVolume } },
        { ShiftMask,                    0x1008ff11,spawn,          {.v = MusicLowerVolume } },
        { ControlMask,                  XK_F11,    spawn,          {.v = AudioLowerVolume } },
        { ShiftMask|ControlMask,        XK_F11,    spawn,          {.v = MusicLowerVolume } },
        { 0,                            0x1008ff13,spawn,          {.v = AudioRaiseVolume } },
        { ShiftMask,                    0x1008ff13,spawn,          {.v = MusicRaiseVolume } },
        { ControlMask,                  XK_F12,    spawn,          {.v = AudioRaiseVolume } },
        { ShiftMask|ControlMask,        XK_F12,    spawn,          {.v = MusicRaiseVolume } },
        { 0,                            0x1008ff12,spawn,          {.v = AudioMute } },
        { 0,                            0x1008ffa9,spawn,          {.v = TouchpadToggle } },

        /* Lock Screen */
        { MODKEY|ShiftMask,             XK_z,      spawn,          {.v = LockScreen } },
        /* Mouse movement with keyboard */

        { MODKEY,                       XK_i,      spawn,          {.v = Mouse} },

        { MODKEY|ShiftMask,             XK_p,      spawn,          {.v = ChBg} },
        { MODKEY|ControlMask|ShiftMask, XK_Return, spawn,          {.v = BlankWin } },
        
        /* Multiple Monitors stuff. If re-enabled, change the incnmaster keys. */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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
