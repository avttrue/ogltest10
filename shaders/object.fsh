struct MaterialProperty
{
    vec3 DiffuseColor;
    vec3 AmbienceColor;
    vec3 SpecularColor;
    float Shines;
};

uniform bool u_IsUseDiffuseMap;
uniform bool u_IsUseNormalMap;
uniform MaterialProperty u_MaterialProperty;
uniform sampler2D u_DiffuseMap;
uniform sampler2D u_NormalMap;
uniform highp vec4 u_LightPosition;
uniform highp float u_LightPower; // сила освещения
varying highp vec4 v_position;
varying highp vec2 v_textcoord;
varying highp vec3 v_normal;
varying highp mat3 v_tbnMatrix;

void main(void)
{
    vec3 usingNormal = v_normal; // используемая нормаль
    if(u_IsUseNormalMap) usingNormal = normalize(texture2D(u_NormalMap, v_textcoord).rgb * 2.0f - 1.0f);

    vec4 eyePosition = vec4(0.0f, 0.0f, 0.0f, 1.0f); // позиция наблюдателя

    vec3 eyeVec = normalize(v_position.xyz - eyePosition.xyz); // направление взгляда
    if(u_IsUseNormalMap) eyeVec = normalize(v_tbnMatrix * eyeVec);

    vec3 lightVec = normalize(v_position.xyz - u_LightPosition.xyz); // вектор освещения
    if(u_IsUseNormalMap) lightVec = normalize(v_tbnMatrix * lightVec);

    vec4 resultColor = vec4(0.0f, 0.0f, 0.0f, 0.0f); // результирующий цвет чёрный
    vec4 diffMatColor = texture2D(u_DiffuseMap, v_textcoord); // диффузный цвет
    vec3 reflectLight = normalize(reflect(lightVec, usingNormal)); // отражённый свет
    float len = length(v_position.xyz - eyePosition.xyz); // расстояние от наблюдателя до точки
    float specularFactor = u_MaterialProperty.Shines; // размер пятна блика
    float ambientFactor = 0.1f; // светимость материала
    vec4 reflectionColor = vec4(1.0f, 1.0f, 1.0f, 1.0f); //цвет блика белый

    if(u_IsUseDiffuseMap == false) diffMatColor = vec4(u_MaterialProperty.DiffuseColor, 1.0f);

    vec4 diffColor = diffMatColor * u_LightPower * max(0.0f, dot(usingNormal, -lightVec));
    resultColor += diffColor;

    vec4 ambientColor = ambientFactor * diffMatColor;
    resultColor += ambientColor * vec4(u_MaterialProperty.AmbienceColor, 1.0f);

    vec4 specularColor = reflectionColor * u_LightPower *
            pow(max(0.0f, dot(reflectLight, -eyeVec)), specularFactor);
    resultColor += specularColor * vec4(u_MaterialProperty.SpecularColor, 1.0f);

    gl_FragColor = resultColor;
}
