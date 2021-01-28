attribute vec4 in_position;
attribute lowp vec4 in_color;

varying lowp vec4 color;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main() {
   color = in_color;
   gl_Position = projectionMatrix * viewMatrix * modelMatrix * in_position;
}
