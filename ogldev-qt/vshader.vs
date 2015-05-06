attribute highp vec4 posAttr;
attribute lowp vec4 colAttr;
varying lowp vec4 col;
attribute vec2 TexCoord;
varying vec2 TexCoord0;
uniform highp mat4 matrix;
void main() {
    col = colAttr;
    gl_Position = matrix * posAttr;
    TexCoord0 = TexCoord;
}
