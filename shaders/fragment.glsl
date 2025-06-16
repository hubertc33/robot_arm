#version 330 core

in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec4 color;
uniform bool useLighting; // << NOWE

out vec4 FragColor;

void main()
{

    // Parametry światła
    vec3 lightColor = vec3(1.0);
    vec3 objectColor = color.rgb;

    // Oblicz kierunki
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    // Komponenty Phonga
    float diff = max(dot(norm, lightDir), 0.0);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); // połysk

    vec3 ambient = 0.2 * lightColor;
    vec3 diffuse = diff * lightColor;
    vec3 specular = 0.5 * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, color.a);
}
