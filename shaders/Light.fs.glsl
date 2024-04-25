#version 330

uniform vec3 uKd; //couleur diffuse
uniform vec3 uKs; //couleur spéculaire
uniform vec3 uKd2; //couleur diffuse
uniform vec3 uKs2; //couleur spéculaire
uniform float uShininess; //brillance du materiau
uniform vec3 uLightDir_vs; //direction de la lumiere
uniform vec3 uLightIntensity; //intensité du soleil
uniform vec3 uLightIntensity2;//intensité de la lumière ponctuelle
uniform vec3 uLightPos_vs;//position de la lumiere ponctuelle


in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

out vec4 fFragColor;

uniform sampler2D TextureCoordinate;

float attenuationByDist(float distance, float constant, float linear, float quadratic) {
    return 1.0 / (constant + linear * distance + quadratic * (distance * distance));
}

vec3 blinnPhongDir() {
    vec3 Wo = normalize(-vPosition_vs);
    vec3 Wi = normalize(uLightDir_vs);

    vec3 halfVector = normalize(Wo + Wi);
    return uLightIntensity * (uKd * dot(Wi, vNormal_vs)) + uKs * pow(max(dot(halfVector, vNormal_vs), 0), uShininess);
}

vec3 blinnPhongPoint() {

    vec3 Wo = normalize(-vPosition_vs);
    vec3 Wi = normalize(uLightPos_vs - vPosition_vs);

    float distance = length(uLightPos_vs - vPosition_vs);
    float attenuation = attenuationByDist(distance, 1.0, 0.1, 0.02);

    vec3 Li = uLightIntensity2 * attenuation;
    vec3 halfVector = normalize(Wo + Wi);

    return Li * (uKd2 * dot(Wi, vNormal_vs)) + uKs2 * pow(dot(halfVector, vNormal_vs), uShininess);
}

void main() {
    vec3 vColor = texture(TextureCoordinate, vTexCoords).xyz;
    vec3 directionalLight = blinnPhongDir();
    vec3 pointLight = blinnPhongPoint();
    vColor *= vec3(clamp(directionalLight+pointLight,0.2,1));
    fFragColor = vec4(vColor, 1.0);
}
