#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D mainTexture;
uniform ivec4 tileCoords;

void main()
{
  vec2 tileSize = vec2(tileCoords.z - tileCoords.x, tileCoords.w - tileCoords.y);
  ivec2 textureSize = textureSize(mainTexture, 0);

  vec2 scaleFactor = tileSize / textureSize;
  vec2 coord = ((texCoord * tileSize) + vec2(tileCoords.xy)) / textureSize;
  FragColor = texture(mainTexture, coord);
}
