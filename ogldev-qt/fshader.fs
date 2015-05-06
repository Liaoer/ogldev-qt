varying lowp vec4 col;
uniform sampler2D gSampler;
varying vec2 TexCoord0;
void main() {
    ///gl_FragColor = col;
    col = texture2D(gSampler, TexCoord0.xy);
}
