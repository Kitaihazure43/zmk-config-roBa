#pragma once

#include <dt-bindings/zmk/keys.h>

// 数字キー上段の記号
#define JP_EXCL  LS(N1)    // !
#define JP_DQT   LS(N2)    // "
#define JP_HASH  LS(N3)    // #
#define JP_DLLR  LS(N4)    // $
#define JP_PRCNT LS(N5)    // %
#define JP_AMPS  LS(N6)    // &
#define JP_SQT   LS(N7)    // '
#define JP_LPAR  LS(N8)    // (
#define JP_RPAR  LS(N9)    // )

// 右上・中段の記号
#define JP_MINUS MINUS     // -
#define JP_EQUAL LS(MINUS) // =
#define JP_CARET EQUAL     // ^
#define JP_TILDE LS(EQUAL) // ~
#define JP_YEN   INT3      // ¥
#define JP_PIPE  LS(INT3)  // |
#define JP_AT    LBKT      // @
#define JP_GRAVE LS(LBKT)  // `
#define JP_LBKT  RBKT      // [
#define JP_LBRC  LS(RBKT)  // {
#define JP_SEMI  SEMI      // ;
#define JP_PLUS  LS(SEMI)  // +
#define JP_COLON SQT       // :
#define JP_ASTRK LS(SQT)   // *
#define JP_RBKT  BSLH      // ]
#define JP_RBRC  LS(BSLH)  // }

// 下段の記号
#define JP_COMMA COMMA     // ,
#define JP_LT    LS(COMMA) // <
#define JP_DOT   DOT       // .
#define JP_GT    LS(DOT)   // >
#define JP_FSLH  FSLH      // /
#define JP_QMARK LS(FSLH)  // ?
#define JP_BSLH  INT1      // \ (バックスラッシュ)
#define JP_UNDER LS(INT1)  // _ (アンダースコア)

// 日本語キーボード固有キー
#define JP_HENK  INT4      // 変換
#define JP_MHEN  INT5      // 無変換
#define JP_KANA  INT2      // カタカナ/ひらがな
