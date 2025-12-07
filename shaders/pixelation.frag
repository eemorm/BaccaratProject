uniform sampler2D texture;
uniform vec2 resolution;
uniform float pixelSize;

void main()
{
    // Compute pixelated UV
    vec2 pix = floor(gl_FragCoord.xy / pixelSize) * pixelSize;
    vec2 uv = pix / resolution;

    gl_FragColor = texture2D(texture, uv);
}