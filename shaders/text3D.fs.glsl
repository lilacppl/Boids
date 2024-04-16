#version 330 core

in vec2 vTexCoords;
uniform sampler2D TextureCoordinate;
// uniform sampler2D CloudTextureCoordinate;

out vec4 FragColor;
// uniform vec4 fFragColor;

void main() {
    // vec4 cloudtxt = texture(CloudTextureCoordinate,vTexCoords);
    vec4 txt = texture(TextureCoordinate,vTexCoords);
    // FragColor = vec4(txt+cloudtxt);
    FragColor = vec4(txt);

    // FragColor.a = 0.6; //transparence
}