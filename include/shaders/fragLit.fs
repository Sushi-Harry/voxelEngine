#version 330

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;

void main(){
    vec3 lightColor = vec3(1.0);
    vec3 objectColor = vec3(0.71, 0.04, 0.04);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;

    FragColor = vec4(abs(Normal), 1.0);
}