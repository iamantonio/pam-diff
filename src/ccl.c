#define CALL_LabelComponent(x, y, returnLabel) { STACK[SP] = x; STACK[SP+1] = y; STACK[SP+2] = returnLabel; SP += 3; goto START; }
#define RETURN { SP -= 3;                \
                 switch (STACK[SP+2])    \
                 {                       \
                 case 1 : goto RETURN1;  \
                 case 2 : goto RETURN2;  \
                 case 3 : goto RETURN3;  \
                 case 4 : goto RETURN4;  \
                 default: return;        \
                 }                       \
               }
#define X (STACK[SP-3])
#define Y (STACK[SP-2])

inline void LabelComponent(uint_fast32_t *STACK, uint_fast32_t width, uint_fast32_t height, bool *input, uint_fast32_t *output, uint_fast32_t labelNo, uint_fast32_t x, uint_fast32_t y) {
    STACK[0] = x;
    STACK[1] = y;
    STACK[2] = 0;  /* return - component is labelled */
    uint_fast32_t SP = 3;
    uint_fast32_t index;
    START: /* Recursive routine starts here */
    index = X + width * Y;
    if (input[index] == false) RETURN;   /* This pixel is not part of a component */
    if (output[index] != 0) RETURN;   /* This pixel has already been labelled  */
    output[index] = labelNo;
    if (X > 0) CALL_LabelComponent(X - 1, Y, 1);   /* left  pixel */
    RETURN1:
    if (X < width - 1) CALL_LabelComponent(X + 1, Y, 2);   /* right pixel */
    RETURN2:
    if (Y > 0) CALL_LabelComponent(X, Y - 1, 3);   /* upper pixel */
    RETURN3:
    if (Y < height - 1) CALL_LabelComponent(X, Y + 1, 4);   /* lower pixel */
    RETURN4:
    RETURN;
}

inline uint_fast32_t LabelImage(uint_fast32_t width, uint_fast32_t height, bool *input, uint_fast32_t *output) {
    //std::cout<<"passed max label "<<maxLabel<<std::endl;
    uint_fast32_t *STACK = (uint_fast32_t *) malloc(3 * sizeof(uint_fast32_t) * (width * height + 1));
    uint_fast32_t labelNo = 0;
    uint_fast32_t index = 0;
    for (uint_fast32_t y = 0; y < height; y++) {
        for (uint_fast32_t x = 0; x < width; x++, index++) {
            if (input[index] == false) continue;   /* This pixel is not part of a component */
            if (output[index] != 0) continue;   /* This pixel has already been labeled  */
            /* New component found */
            labelNo++;
            LabelComponent(STACK, width, height, input, output, labelNo, x, y);
        }
    }
    free(STACK);
    return labelNo + 1;
}
