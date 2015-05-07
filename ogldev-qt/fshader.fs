varying vec2 TexCoord0;
varying lowp vec4 col;

uniform sampler2D gSampler;
void main() {
    //gl_FragColor = col;
    gl_FragColor = texture2D(gSampler, TexCoord0.xy);

}
