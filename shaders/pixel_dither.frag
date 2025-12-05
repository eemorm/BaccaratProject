// pixel_dither_fade.frag
uniform sampler2D texture;   // scene texture
uniform vec2 resolution;     // screen resolution
uniform float pixelSize;     // size of pixel blocks

// 4x4 Bayer matrix constants
const float d00 = 0.0/16.0;  const float d01 = 8.0/16.0;  const float d02 = 2.0/16.0;  const float d03 = 10.0/16.0;
const float d10 = 12.0/16.0; const float d11 = 4.0/16.0;  const float d12 = 14.0/16.0; const float d13 = 6.0/16.0;
const float d20 = 3.0/16.0;  const float d21 = 11.0/16.0; const float d22 = 1.0/16.0;  const float d23 = 9.0/16.0;
const float d30 = 15.0/16.0; const float d31 = 7.0/16.0;  const float d32 = 13.0/16.0; const float d33 = 5.0/16.0;

float getThreshold(int x, int y)
{
    if (y == 0) { if (x == 0) return d00; else if (x == 1) return d01; else if (x == 2) return d02; else return d03; }
    if (y == 1) { if (x == 0) return d10; else if (x == 1) return d11; else if (x == 2) return d12; else return d13; }
    if (y == 2) { if (x == 0) return d20; else if (x == 1) return d21; else if (x == 2) return d22; else return d23; }
    if (y == 3) { if (x == 0) return d30; else if (x == 1) return d31; else if (x == 2) return d32; else return d33; }
    return 0.0;
}

void main()
{
    // Pixelation
    vec2 pix = floor(gl_FragCoord.xy / pixelSize) * pixelSize;
    vec2 uv = pix / resolution;

    vec4 color = texture2D(texture, uv);

    // Bayer dithering
    int x = int(mod(gl_FragCoord.x, 4.0));
    int y = int(mod(gl_FragCoord.y, 4.0));
    float threshold = getThreshold(x, y);

    // Dithering effect (soft)
    vec3 dithered = step(vec3(threshold), color.rgb);

    // Distance-based fade for dithering only
    vec2 center = resolution * 0.5;
    float dist = distance(gl_FragCoord.xy, center) / length(resolution * 0.5); // 0=center, 1=edge
    float fadeFactor = clamp(1.0 - dist, 0.0, 1.0); // fade toward edges

    // Combine original color with soft dithering fade
    color.rgb = mix(color.rgb, dithered, 0.4 * fadeFactor); // 0.4 controls dithering strength

    gl_FragColor = color;
}
