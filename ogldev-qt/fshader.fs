uniform sampler2D texture;

varying vec2 v_texcoord;
varying lowp vec4 col;

void main() {
    //gl_FragColor = col;
    gl_FragColor = texture2D(texture, v_texcoord);

}
