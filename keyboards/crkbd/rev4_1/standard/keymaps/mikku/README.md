# Mikku's Corne v4.1 Keymap

Corne v4.1 (crkbd rev4_1) standard layout with Callum-style one-shot mods.

**Board:** crkbd/rev4_1/standard (RP2040)
**Layout:** `LAYOUT_split_3x6_3_ex2` (44 keys, outer columns + ex2 inner keys unused)

## Features

- **Callum one-shot mods** — custom implementation (no timers) that survives layer changes
- **Combos** — D+F / J+K for NUM layer, B+N for Caps Word
- **OSM Shift** on left thumb — tap for one-shot, hold for regular shift
- **Tri-layer** — hold EXT + SYM simultaneously to activate FUNC layer
- **RGB per layer** — color-coded layer indicators on both halves

## Layers

### Layer 0: BASE (default RGB animation)

```
.------.------.------.------.------.          .------.------.------.------.------.
|  Q   |  W   |  E   |  R   |  T   |          |  Y   |  U   |  I   |  O   |  P   |
|------+------+------+------+------|          |------+------+------+------+------|
|  A   |  S   |  D   |  F   |  G   |          |  H   |  J   |  K   |  L   |  '   |
|------+------+------+------+------|          |------+------+------+------+------|
|  Z   |  X   |  C   |  V   |  B   |          |  N   |  M   |  ,   |  .   |  /   |
'------'------'------+------+------+------.  .------+------+------'------'------'
                     | EXT  | SHFT | SPC  |  | ENT  | SYM  | BSPC |
                     '------'------'------'  '------'------'------'
```

- **EXT** = `MO(_EXT)` — hold for navigation + left-side Callum mods
- **SYM** = `MO(_SYM)` — hold for symbols + right-side Callum mods
- **SHFT** = `OSM(MOD_LSFT)` — tap = one-shot shift, hold = regular shift
- **D+F** or **J+K** (combo hold) = `MO(_NUM)` — numbers + nav
- **B+N** (combo tap) = Caps Word toggle

### Layer 1: NUM (RGB: blue)

Activated by holding D+F or J+K combo.

```
.------.------.------.------.------.          .------.------.------.------.------.
|  1   |  2   |  3   |  4   |  5   |          |  6   |  7   |  8   |  9   |  0   |
|------+------+------+------+------|          |------+------+------+------+------|
|  ä   |  å   |  ö   |      |      |          |  <-  |  v   |  ^   |  ->  |      |
|------+------+------+------+------|          |------+------+------+------+------|
|      |      |      | ESC  | TAB  |          |      |      |      |      |      |
'------'------'------+------+------+------.  .------+------+------'------'------'
                     | DEL  | TAB  | SPC  |  | ENT  | BSPC | BSPC |
                     '------'------'------'  '------'------'------'
```

- `ä`, `å`, `ö` = `RALT(KC_Q)`, `RALT(KC_W)`, `RALT(KC_P)` (special characters) this is due to requirement of typing finnish or swedish and needing simple access to these keys. Requires host OS input to allow for `us intl altgr` variation.
- Arrows on right home row

### Layer 2: SYM (RGB: purple)

Activated by holding right thumb SYM key.

```
.------.------.------.------.------.          .------.------.------.------.------.
|  ~   |  =   |  +   |  {   |  %   |          |  &   |  }   |  *   |  !   |  @   |
|------+------+------+------+------|          |------+------+------+------+------|
|  `   |  :   |  _   |  -   |  [   |          |  ]   | CTRL | SHFT | ALT  | GUI  |
|------+------+------+------+------|          |------+------+------+------+------|
|  |   |  ;   |  #   |  (   |  <   |          |  >   |  )   |  ^   |  $   |  \   |
'------'------'------+------+------+------.  .------+------+------'------'------'
                     |      |      | SPC  |  | ENT  |      |      |
                     '------'------'------'  '------'------'------'
```

- **Callum mods on right home row** (CTRL, SHFT, ALT, GUI)
- Opening brackets on left, closing on right: `{}`  `[]`  `()`  `<>`

### Layer 3: EXT (RGB: green)

Activated by holding left thumb EXT key.

```
.------.------.------.------.------.          .------.------.------.------.------.
| ESC  |      |      |      | INS  |          | INS  | PGDN | PGUP |      |      |
|------+------+------+------+------|          |------+------+------+------+------|
| GUI  | ALT  | SHFT | CTRL |      |          |  <-  |  v   |  ^   |  ->  | DEL  |
|------+------+------+------+------|          |------+------+------+------+------|
|      |      | TAB  | ESC  |      |          |      | BSPC | HOME | END  | PSCR |
'------'------'------+------+------+------.  .------+------+------'------'------'
                     |      |      |      |  | ENT  |      |      |
                     '------'------'------'  '------'------'------'
```

- **Callum mods on left home row** (GUI, ALT, SHFT, CTRL)
- Navigation on right side

### Layer 4: FUNC (RGB: red)

Activated automatically by holding EXT + SYM simultaneously (tri-layer).

```
.------.------.------.------.------.          .------.------.------.------.------.
| STOP | PLAY | VOL- | VOL+ | MUTE |          |      |  F7  |  F8  |  F9  | F10  |
|------+------+------+------+------|          |------+------+------+------+------|
| GUI  | ALT  | SHFT | CTRL |      |          | BRI+ |  F4  |  F5  |  F6  | F11  |
|------+------+------+------+------|          |------+------+------+------+------|
|      |      |      |      |      |          | BRI- |  F1  |  F2  |  F3  | F12  |
'------'------'------+------+------+------.  .------+------+------'------'------'
                     |      |      |      |  | ENT  |      |      |
                     '------'------'------'  '------'------'------'
```

## How Callum One-Shot Mods Work

Unlike QMK's built-in `OSM()`, these custom one-shot mods have **no timeout** and **survive layer changes**:

1. **Hold** a layer key (EXT or SYM)
2. **Tap** a mod key (e.g. CTRL) — the mod is now "armed"
3. **Release** the layer key — you're back on BASE, mod stays armed
4. **Tap** any key (e.g. `A`) — sends `Ctrl+A`, mod is consumed

**Stacking:** You can arm multiple mods. Hold EXT, tap CTRL, tap SHFT, release EXT, tap `A` = `Ctrl+Shift+A`.

**Cancel:** Tapping a layer key without pressing a mod cancels any armed mods.

**Hold behavior:** If you hold the mod key and press another key while still holding it, it acts as a regular held modifier (not one-shot).

## RGB Layer Colors

| Layer | Color | Hex |
|-------|-------|-----|
| BASE  | Default animation | — |
| NUM   | Blue   | `#0000FF` |
| SYM   | Purple | `#7F00FF` |
| EXT   | Green  | `#00FF00` |
| FUNC  | Red    | `#FF0000` |

## Building

```sh
qmk compile -kb crkbd/rev4_1/standard -km mikku
```

## Flashing

1. Unplug keyboard
2. Hold boot button on PCB, plug in USB
3. Drag `crkbd_rev4_1_standard_mikku.uf2` onto the `RPI-RP2` drive
4. Repeat for the other half

Both halves must be flashed with the same firmware.



Special thanks to @fhoekstra for the nudge to go for callum style osm and for his keymap that i have conveniently stolen for now. Arigato
