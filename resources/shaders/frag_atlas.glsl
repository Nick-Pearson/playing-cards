#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D mainTexture;
uniform vec2 tileID;
//uniform vec2 tileSize;

void main()
{
  vec2 tileSize = vec2(140, 190);
  ivec2 textureSize = textureSize(mainTexture, 0);

  vec2 scaleFactor = tileSize / textureSize;
  vec2 coord = (texCoord + tileID) * scaleFactor;
  FragColor = texture(mainTexture, coord);
}
