/** *********************************************************************** **/
/** *********************************************************************** **/
/**     Created by:     Ruan (Baggins) Luies 23511354                       **/
/**     email:          23511354@nwu.ac.za                                  **/
/**     Project name:   Virtual Concierge Creator And Management System     **/
/**     File Name:      mainVert.vert                                       **/
/**     From Date:      2015/02/24                                          **/
/**     To Date:        2015/10/01                                          **/
/** **********************************************************************  **/
/** *********************************************************************** **/
attribute highp vec4 vertex;
uniform highp mat4 mvpMatrix;
uniform highp mat4 wvpMatrix;
uniform highp mat4 rotationMatrix;
attribute vec3 normal;
varying vec3 normals;
varying highp vec4 posi;
attribute vec2 textureCoordinate;
varying vec2 varyingTextureCoordinate;
void main()
{
    gl_Position = wvpMatrix * mvpMatrix * vertex;
    posi = mvpMatrix * vertex;
    vec4 norm = rotationMatrix * vec4(normal,1);
    normals = norm.xyz;
    varyingTextureCoordinate = textureCoordinate;
}
