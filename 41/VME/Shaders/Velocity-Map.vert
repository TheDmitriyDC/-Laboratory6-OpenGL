#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 FragPos;
out vec3 Normal;

out vec4 L_P;
out vec4 N_P;

uniform mat4 model = mat4(0.0f);
uniform mat4 view = mat4(0.0f);
uniform mat4 projection = mat4(0.0f);

uniform mat4 PP = mat4(0.0f); // Previous Projection
uniform mat4 PV = mat4(0.0f); // Previous View
uniform mat4 PM = mat4(0.0f); // Previous Model

bool MDL = true; // Model Projection Calculation

void main()
{
    vec4 VP = view * model * vec4(aPos, 1.0);
    FragPos = VP.xyz;
    
    if (MDL)
    {
        N_P = projection * view * model * vec4(aPos, 1.0f);
	    L_P = PP * PV * PM * vec4(aPos, 1.0f);
    }
    else
    {
        N_P = projection * view * vec4(aPos, 1.0f);
	    L_P = PP * PV * vec4(aPos, 1.0f);
    }

    
    gl_Position = projection * VP;
}