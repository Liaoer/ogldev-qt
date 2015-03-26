attribute highp vec3 posAttr;
attribute lowp vec4 colAttr;
varying lowp vec4 col;
uniform highp mat4 matrix;
void main() {
    col = vec4(clamp(posAttr, 0.0, 1.0), 1.0);
    gl_Position = matrix * vec4(posAttr, 1.0);
}
