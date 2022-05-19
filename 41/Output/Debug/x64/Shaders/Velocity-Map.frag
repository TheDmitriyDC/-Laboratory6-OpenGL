#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
 
in vec4 L_P;
in vec4 N_P;

void main()
{
    vec2 TN_P; vec2 TL_P;
    TN_P = (((N_P.xy / N_P.w) * 0.5) + 0.5f);
    TL_P = (((L_P.xy / L_P.w) * 0.5) + 0.5f);
    vec2 GV = vec2(TN_P - TL_P);
    FragColor = vec4(vec3(GV, 0.0f), 0.0f);
}