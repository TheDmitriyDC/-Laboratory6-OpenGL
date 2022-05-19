#version 330 core
out vec4 FragColor;

uniform sampler2D screenTexture; // Screen texture
uniform sampler2D screenVelocity; // Velocity Map

in vec2 TexCoords;

uniform float TF = 120; // Target framerate
uniform float CF = 360; // Current framerate

float VS = 0.4f; // Velocity Strength

void main()
{
    vec2 texelSize = 1.0 / vec2(textureSize(screenTexture, 0));
    vec2 screenTexCoords = gl_FragCoord.xy * texelSize;

    VS = CF / TF; // Calculates velocity strength based on framerate.

    vec2 velocity = texture(screenVelocity, TexCoords).rg; // Takes red and green values from velocity map.
    velocity *= VS;

    float speed = length(velocity / texelSize);
    int nSamples = clamp(int(speed), 2, 64); // Clamps samples beetween minimum available and maximum possible.

    // Blurring Part
    vec4 oResult = texture(screenTexture, screenTexCoords);
    for (int i = 1; i < nSamples; ++i)
    {
        vec2 offset = velocity * (float(i) / float(nSamples - 1) - 0.5);
        oResult += texture(screenTexture, screenTexCoords + offset);
    }
    oResult /= float(nSamples);
    // -------------

    /* Comparison
    vec4 TR = texture(screenTexture, TexCoords);
    vec4 TS = oResult;
    FragColor = mix(TS, TR, step(0.5f, TexCoords.x));
    */

    FragColor = oResult;
}
