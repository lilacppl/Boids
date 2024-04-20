#version 330

uniform vec3 uKd; //couleur diffuse
uniform vec3 uKs; //couleur spéculaire
uniform vec3 uKd2; //couleur diffuse
uniform vec3 uKs2; //couleur spéculaire
uniform float uShininess; //brillance du materiau
uniform vec3 uLightDir_vs; //direction de la lumiere
uniform vec3 uLightIntensity;

uniform vec3 uLightPos_vs;//position de la lumiere ponctuelle


in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

out vec4 fFragColor;

uniform sampler2D TextureCoordinate;


vec3 blinnPhongDir(vec3 fragPos, vec3 normal) {

    vec3 lightDir = normalize(uLightDir_vs); // Direction incidente de la lumière
    vec3 halfVector = normalize(lightDir + normalize(-fragPos)); // Vecteur halfVector
    float diffuseFactor = max(dot(normal, lightDir), 0.0); // Produit scalaire entre la normale et la direction incidente
    float specularFactor = pow(max(dot(normal, halfVector), 0.0), uShininess); // Produit scalaire entre le vecteur halfVector et la normale
    vec3 diffuseColor = uLightIntensity * uKd * diffuseFactor; // Calcul de la couleur diffuse
    vec3 specularColor = uLightIntensity * uKs * specularFactor; // Calcul de la couleur glossy    
    return diffuseColor + specularColor; 
}

vec3 blinnPhongPoint(vec3 fragPos, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(uLightPos_vs - fragPos); // Vecteur de la lumière au fragment
    float distance = length(lightDir); // Distance entre la lumière et le fragment
    lightDir = normalize(lightDir); // Normalisation du vecteur direction lumière
    float attenuation = 1.0 / (distance * distance); // Atténuation quadratique
    vec3 lightIntensity = uLightIntensity * attenuation; // Intensité de la lumière atténuée

    vec3 halfVector = normalize(lightDir + viewDir); // Vecteur halfVector
    float diffuseFactor = max(dot(normal, lightDir), 0.0); // Produit scalaire entre la normale et la direction incidente
    float specularFactor = pow(max(dot(normal, halfVector), 0.0), uShininess); // Produit scalaire entre le vecteur halfVector et la normale

    vec3 diffuseColor = lightIntensity * uKd2 * diffuseFactor; // Calcul de la couleur diffuse
    vec3 specularColor = lightIntensity * uKs2 * specularFactor; // Calcul de la couleur glossy    
    return diffuseColor + specularColor; // Couleur finale en combinant diffuse et glossy
}

void main() {
    vec3 vColor = texture(TextureCoordinate, vTexCoords).xyz;

    vec3 viewDir = normalize(-vPosition_vs);
    vec3 directionalLight = blinnPhongDir(vPosition_vs, vNormal_vs);
    vec3 pointLight = blinnPhongPoint(vPosition_vs, vNormal_vs, viewDir);

    vColor *= vec3(clamp(directionalLight+pointLight,0,1));
    // vColor *= vec3(clamp(directionalLight,0,1));

    fFragColor = vec4(vColor, 1.0);
}
