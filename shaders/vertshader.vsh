uniform highp mat4 u_ProjectionMatrix;
uniform highp mat4 u_ViewMatrix;
uniform highp mat4 u_ModelMatrix;

attribute highp vec4 a_position;
attribute highp vec2 a_textcoord;
attribute highp vec3 a_normal;
attribute highp vec3 a_tangent;
attribute highp vec3 a_bitangent;

varying highp vec4 v_position;
varying highp vec2 v_textcoord;
varying highp vec3 v_normal;
varying highp mat3 v_tbnMatrix;

highp mat3 transpose(in highp mat3 inMatrix)
{
    highp vec3 i0 = inMatrix[0];
    highp vec3 i1 = inMatrix[1];
    highp vec3 i2 = inMatrix[2];

    highp mat3 outMatrix = mat3(
                vec3(i0.x, i1.x, i2.x),
                vec3(i0.y, i1.y, i2.y),
                vec3(i0.z, i1.z, i2.z));
    return outMatrix;
}

void main(void)
{
    mat4 mv_matrix = u_ViewMatrix * u_ModelMatrix;

    gl_Position = u_ProjectionMatrix * mv_matrix * a_position;

    v_textcoord = a_textcoord;
    v_normal = normalize(vec3(mv_matrix * vec4(a_normal, 0.0f)));
    v_position = mv_matrix * a_position;

    vec3 tangent = normalize(vec4(mv_matrix * vec4(a_tangent, 0.0f)).xyz);
    vec3 bitangent = normalize(vec4(mv_matrix * vec4(a_bitangent, 0.0f)).xyz);
    vec3 normal = normalize(vec4(mv_matrix * vec4(a_normal, 0.0f)).xyz);

    v_tbnMatrix = transpose(mat3(tangent, bitangent, normal));
}
