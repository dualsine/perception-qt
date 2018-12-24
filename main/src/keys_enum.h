#ifndef KEYS_ENUM_H_
#define KEYS_ENUM_H_

#include <X11/X.h>
#include <X11/Xlib.h>

#undef Bool
#undef CursorShape
#undef Expose
#undef KeyPress
#undef KeyRelease
#undef FocusIn
#undef FocusOut
#undef FontChange
#undef None
#undef Status
#undef Unsorted

#include <QObject>
#include "cef/include/cef_app.h"
#include "cef/include/base/cef_macros.h"

namespace KeysEnum {

  Qt::KeyboardModifier getModifier(CefEventHandle os_event) {
    Qt::KeyboardModifier mod = Qt::NoModifier;
    if (os_event->xkey.state & ShiftMask) mod = Qt::ShiftModifier;
    if (os_event->xkey.state & ControlMask) mod = Qt::ControlModifier;
    return mod;
  }

  Qt::Key getQtKeyCodeFromGtk(CefEventHandle os_event) {
    static const unsigned int kHardwareCodeToGDKKeyval[] = {
        0,                 // 0x00:
        0,                 // 0x01:
        0,                 // 0x02:
        0,                 // 0x03:
        0,                 // 0x04:
        0,                 // 0x05:
        0,                 // 0x06:
        0,                 // 0x07:
        0,                 // 0x08:
        Qt::Key_Escape,                 // 0x09: GDK_Escape
        Qt::Key_1,             // 0x0A: GDK_1
        Qt::Key_2,             // 0x0B: GDK_2
        Qt::Key_3,             // 0x0C: GDK_3
        Qt::Key_4,             // 0x0D: GDK_4
        Qt::Key_5,             // 0x0E: GDK_5
        Qt::Key_6,             // 0x0F: GDK_6
        Qt::Key_7,             // 0x10: GDK_7
        Qt::Key_8,             // 0x11: GDK_8
        Qt::Key_9,             // 0x12: GDK_9
        Qt::Key_0,             // 0x13: GDK_0
        Qt::Key_Minus,         // 0x14: GDK_minus
        Qt::Key_Equal,         // 0x15: GDK_equal
        Qt::Key_Backspace,                 // 0x16: GDK_BackSpace
        Qt::Key_Tab,                 // 0x17: GDK_Tab
        Qt::Key_Q,             // 0x18: GDK_q
        Qt::Key_W,             // 0x19: GDK_w
        Qt::Key_E,             // 0x1A: GDK_e
        Qt::Key_R,             // 0x1B: GDK_r
        Qt::Key_T,             // 0x1C: GDK_t
        Qt::Key_Y,             // 0x1D: GDK_y
        Qt::Key_U,             // 0x1E: GDK_u
        Qt::Key_I,             // 0x1F: GDK_i
        Qt::Key_O,             // 0x20: GDK_o
        Qt::Key_P,             // 0x21: GDK_p
        Qt::Key_BracketLeft,   // 0x22: GDK_bracketleft
        Qt::Key_BracketRight,  // 0x23: GDK_bracketright
        Qt::Key_Enter,                 // 0x24: GDK_Return
        0,                 // 0x25: GDK_Control_L
        Qt::Key_A,             // 0x26: GDK_a
        Qt::Key_S,             // 0x27: GDK_s
        Qt::Key_D,             // 0x28: GDK_d
        Qt::Key_F,             // 0x29: GDK_f
        Qt::Key_G,             // 0x2A: GDK_g
        Qt::Key_H,             // 0x2B: GDK_h
        Qt::Key_J,             // 0x2C: GDK_j
        Qt::Key_K,             // 0x2D: GDK_k
        Qt::Key_L,             // 0x2E: GDK_l
        Qt::Key_Semicolon,     // 0x2F: GDK_semicolon
        Qt::Key_Apostrophe,    // 0x30: GDK_apostrophe
        0,         // 0x31: GDK_grave
        0,                 // 0x32: GDK_Shift_L
        Qt::Key_Backslash,     // 0x33: GDK_backslash
        Qt::Key_Z,             // 0x34: GDK_z
        Qt::Key_X,             // 0x35: GDK_x
        Qt::Key_C,             // 0x36: GDK_c
        Qt::Key_V,             // 0x37: GDK_v
        Qt::Key_B,             // 0x38: GDK_b
        Qt::Key_N,             // 0x39: GDK_n
        Qt::Key_M,             // 0x3A: GDK_m
        Qt::Key_Comma,         // 0x3B: GDK_comma
        Qt::Key_Period,        // 0x3C: GDK_period
        Qt::Key_Slash,         // 0x3D: GDK_slash
        0,                 // 0x3E: GDK_Shift_R
        0,                 // 0x3F:
        0,                 // 0x40:
        0,                 // 0x41:
        0,                 // 0x42:
        0,                 // 0x43:
        0,                 // 0x44:
        0,                 // 0x45:
        0,                 // 0x46:
        0,                 // 0x47:
        0,                 // 0x48:
        0,                 // 0x49:
        0,                 // 0x4A:
        0,                 // 0x4B:
        0,                 // 0x4C:
        0,                 // 0x4D:
        0,                 // 0x4E:
        0,                 // 0x4F:
        0,                 // 0x50:
        0,                 // 0x51:
        0,                 // 0x52:
        0,                 // 0x53:
        0,                 // 0x54:
        0,                 // 0x55:
        0,                 // 0x56:
        0,                 // 0x57:
        0,                 // 0x58:
        0,                 // 0x59:
        0,                 // 0x5A:
        0,                 // 0x5B:
        0,                 // 0x5C:
        0,                 // 0x5D:
        0,                 // 0x5E:
        0,                 // 0x5F:
        0,                 // 0x60:
        0,                 // 0x61:
        0,                 // 0x62:
        0,                 // 0x63:
        0,                 // 0x64:
        0,                 // 0x65:
        0,                 // 0x66:
        0,                 // 0x67:
        0,                 // 0x68:
        0,                 // 0x69:
        0,                 // 0x6A:
        0,                 // 0x6B:
        0,                 // 0x6C:
        0,                 // 0x6D:
        0,                 // 0x6E:
        Qt::Key_Up,                 // 0x6F: GDK_Up
        0,                 // 0x70:
        Qt::Key_Left,                 // 0x71: GDK_Left
        Qt::Key_Right,                 // 0x72: GDK_Right
        Qt::Key_Super_L,       // 0x73: GDK_Super_L
        Qt::Key_Down,       // 0x74: GDK_Down
    };

      // |windows_key_code| has to include a valid virtual-key code even when we
      // use non-US layouts, e.g. even when we type an 'A' key of a US keyboard
      // on the Hebrew layout, |windows_key_code| should be VK_A.
      // On the other hand, |event->keyval| value depends on the current
      // GdkKeymap object, i.e. when we type an 'A' key of a US keyboard on
      // the Hebrew layout, |event->keyval| becomes GDK_hebrew_shin and this
      // KeyboardCodeFromXKeysym() call returns 0.
      // To improve compatibilty with Windows, we use |event->hardware_keycode|
      // for retrieving its Windows key-code for the keys when the
      // WebCore::windows_key_codeForEvent() call returns 0.
      // We shouldn't use |event->hardware_keycode| for keys that GdkKeymap
      // objects cannot change because |event->hardware_keycode| doesn't change
      // even when we change the layout options, e.g. when we swap a control
      // key and a caps-lock key, GTK doesn't swap their
      // |event->hardware_keycode| values but swap their |event->keyval| values.
//    KeyboardCode windows_key_code = KeyboardCodeFromXKeysym(event->keyval);
//    if (windows_key_code)
//      return windows_key_code;

    uint gtk_code = os_event->xkey.keycode;
    Qt::Key keyval;
    uint table_size = arraysize(kHardwareCodeToGDKKeyval);
    if (gtk_code < table_size) {
      keyval = static_cast<Qt::Key>(kHardwareCodeToGDKKeyval[gtk_code]);
    } else keyval = Qt::Key_notsign;

    // This key is one that keyboard-layout drivers cannot change.
    // Use |event->keyval| to retrieve its |windows_key_code| value.
    return keyval;
  }

} // namespace KeysEnum

#endif // KEY_ENUM_H
