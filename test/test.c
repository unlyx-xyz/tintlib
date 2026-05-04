#define TINT_LIB_IMPLEMENTATION
#include "../tintlib.h"

#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool cmpseq3bit4bitElements(TL_Sequence s1, TL_Sequence s2) {
    return  s1.c3bit4bit.foreground == s2.c3bit4bit.foreground &&
            s1.c3bit4bit.background == s2.c3bit4bit.background;
}

bool cmpseq8bitElements(TL_Sequence s1, TL_Sequence s2) {
    return  s1.c8bit.foreground == s2.c8bit.foreground &&
            s1.c8bit.background == s2.c8bit.background;
}

bool cmpseqTruecolorElements(TL_Sequence s1, TL_Sequence s2) {
    return  s1.ctruecolor.background.enable == s2.ctruecolor.background.enable &&
            s1.ctruecolor.background.r == s2.ctruecolor.background.r &&
            s1.ctruecolor.background.g == s2.ctruecolor.background.g &&
            s1.ctruecolor.background.b == s2.ctruecolor.background.b &&
            s1.ctruecolor.foreground.enable == s2.ctruecolor.foreground.enable &&
            s1.ctruecolor.foreground.r == s2.ctruecolor.foreground.r &&
            s1.ctruecolor.foreground.g == s2.ctruecolor.foreground.g &&
            s1.ctruecolor.foreground.b == s2.ctruecolor.foreground.b;
}

bool cmpseqDaElements(TL_Sequence s1, TL_Sequence s2) {
    return  s1.da.blinking == s2.da.blinking &&
            s1.da.bold == s2.da.bold &&
            s1.da.dim == s2.da.dim &&
            s1.da.italic == s2.da.italic &&
            s1.da.hidden == s2.da.hidden &&
            s1.da.inverse == s2.da.inverse &&
            s1.da.underline == s2.da.underline &&
            s1.da.strikethrough == s2.da.strikethrough;
}

void cmpseq(int type, TL_Sequence s1, TL_Sequence s2) {

    switch(type) {
        
        case -1:
            assert(cmpseqDaElements(s1, s2));
            assert(cmpseq3bit4bitElements(s1, s2));
            assert(cmpseq8bitElements(s1, s2));
            assert(cmpseqTruecolorElements(s1, s2));
            break;

        case ANSI_C1_CSI_SGR_3BIT4BIT:
            assert(cmpseq3bit4bitElements(s1, s2));
            break;

        case ANSI_C1_CSI_SGR_8BIT:
            assert(cmpseq8bitElements(s1, s2));
            break;

        case ANSI_C1_CSI_SGR_TRUECOLOR:
            assert(cmpseqTruecolorElements(s1, s2));
            break;

        case ANSI_C1_CSI_SGR_DISPLAYATTRIBUTES:
            assert(cmpseqDaElements(s1, s2));
            break;

    };

}

#define validateOutput(msg, status, code)\
    do {\
        if (status == true || status >= 1) {\
            assert(strstr(msg, code));\
        }\
    } while(0)\

void validateDaOutput(char* buff, TL_Sequence seq) {
    validateOutput(buff, seq.da.bold, TL_SGRDisplayAttributesPS[ANSI_C1_CSI_SGR_BOLD]);
    validateOutput(buff, seq.da.blinking, TL_SGRDisplayAttributesPS[ANSI_C1_CSI_SGR_BLINKING]);
    validateOutput(buff, seq.da.dim, TL_SGRDisplayAttributesPS[ANSI_C1_CSI_SGR_DIM]);
    validateOutput(buff, seq.da.hidden, TL_SGRDisplayAttributesPS[ANSI_C1_CSI_SGR_HIDDEN]);
    validateOutput(buff, seq.da.inverse, TL_SGRDisplayAttributesPS[ANSI_C1_CSI_SGR_INVERSE]);
    validateOutput(buff, seq.da.italic, TL_SGRDisplayAttributesPS[ANSI_C1_CSI_SGR_ITALIC]);
    validateOutput(buff, seq.da.underline, TL_SGRDisplayAttributesPS[ANSI_C1_CSI_SGR_UNDERLINE]);
    validateOutput(buff, seq.da.strikethrough, TL_SGRDisplayAttributesPS[ANSI_C1_CSI_SGR_STRIKETHROUGH]);
}

void validatec3bit4bitOutput(char* buff, TL_Sequence seq) {
    validateOutput(buff, seq.c3bit4bit.foreground, TL_SGRColors3Bit4BitPS[seq.c3bit4bit.foreground]);
    validateOutput(buff, seq.c3bit4bit.background, TL_SGRColors3Bit4BitPS[seq.c3bit4bit.background]);
};

void validatec8bitOutput(char* buff, TL_Sequence seq) {
    char foreground_value[4] = {0}; snprintf(foreground_value, sizeof(foreground_value), "%d", seq.c8bit.foreground);
    char background_value[4] = {0}; snprintf(background_value, sizeof(background_value), "%d", seq.c8bit.background);
    validateOutput(buff, seq.c8bit.foreground, foreground_value);
    validateOutput(buff, seq.c8bit.background, background_value);
}

void validatecTruecolorOutput(char* buff, TL_Sequence seq) {
    char foreground_r_value[4] = {0}; snprintf(foreground_r_value, sizeof(foreground_r_value), "%d", seq.ctruecolor.foreground.r);
    char background_r_value[4] = {0}; snprintf(background_r_value, sizeof(background_r_value), "%d", seq.ctruecolor.background.r);
    char foreground_g_value[4] = {0}; snprintf(foreground_g_value, sizeof(foreground_g_value), "%d", seq.ctruecolor.foreground.g);
    char background_g_value[4] = {0}; snprintf(background_g_value, sizeof(background_g_value), "%d", seq.ctruecolor.background.g);
    char foreground_b_value[4] = {0}; snprintf(foreground_b_value, sizeof(foreground_b_value), "%d", seq.ctruecolor.foreground.b);
    char background_b_value[4] = {0}; snprintf(background_b_value, sizeof(background_b_value), "%d", seq.ctruecolor.background.b);
    validateOutput(buff, seq.ctruecolor.foreground.enable, foreground_r_value);
    validateOutput(buff, seq.ctruecolor.background.enable, background_r_value);
    validateOutput(buff, seq.ctruecolor.foreground.enable, foreground_g_value);
    validateOutput(buff, seq.ctruecolor.background.enable, background_g_value);
    validateOutput(buff, seq.ctruecolor.foreground.enable, foreground_b_value);
    validateOutput(buff, seq.ctruecolor.background.enable, background_b_value);
}

void validateprintf(TL_Sequence seq) {
    
    char buff[512] = {0};
    FILE* stream = fmemopen(buff, sizeof(buff), "w");

    TL_fprintfDa(stream, seq, "Hello %s!", "tintlib");
    fflush(stream);
    validateDaOutput(buff, seq);

    memset(buff, 0, sizeof(buff));
    rewind(stream);
    TL_fprintfc3bit4bit(stream, seq, "Hello %s!", "tintlib");
    fflush(stream);
    validatec3bit4bitOutput(buff, seq);

    memset(buff, 0, sizeof(buff));
    rewind(stream);
    TL_fprintfc8bit(stream, seq, "Hello %s!", "tintlib");
    fflush(stream);
    validatec8bitOutput(buff, seq);

    memset(buff, 0, sizeof(buff));
    rewind(stream);
    TL_fprintfcTruecolor(stream, seq, "Hello %s!", "tintlib");
    fflush(stream);
    validatecTruecolorOutput(buff, seq);

    fflush(stream);
    fclose(stream);

}

int main(void) {

    TL_Sequence s1 = {0}, s2 = {0}, s3 = {0}, s4 = {0}, s5 = {0}, s6 = {0};
    s1.da.bold = true;
    s1.da.underline = true;
    s1.da.italic = true;
    s1.da.blinking = true;
    s1.c3bit4bit.foreground = ANSI_C1_CSI_SGR_FG_YELLOW;
    s1.c3bit4bit.background = ANSI_C1_CSI_SGR_BG_CYAN;
    s1.c8bit.foreground = 109;
    s1.c8bit.background = -1;
    s1.ctruecolor.foreground = (TL_RGB){.enable = true, .r = 0, .g = 255, .b = 0};
    s1.ctruecolor.background = (TL_RGB){.enable = false, .r = 0, .g = 0, .b = 0};

    TL_CopySequenceDa(s1, &s2);
    TL_CopySequence3bit4bit(s1, &s3);
    TL_CopySequence8bit(s1, &s4);
    TL_CopySequenceTruecolor(s1, &s5);
    TL_CopySequence(s1, &s6);

    cmpseq(ANSI_C1_CSI_SGR_DISPLAYATTRIBUTES, s1, s2);
    cmpseq(ANSI_C1_CSI_SGR_3BIT4BIT, s1, s3);
    cmpseq(ANSI_C1_CSI_SGR_8BIT, s1, s4);
    cmpseq(ANSI_C1_CSI_SGR_TRUECOLOR, s1, s5);
    cmpseq(-1, s1, s6);

    validateprintf(s1);

    return 0;

}
