attribute highp vec4 posAttr;
attribute lowp vec4 colAttr;
attribute vec2 a_texcoord;

varying vec2 v_texcoord;
varying lowp vec4 col;
uniform highp mat4 matrix;
void main() {
    col = colAttr;
    gl_Position = matrix * posAttr;
    v_texcoord = a_texcoord;
}
