uniform vec2 u_center;
uniform float u_radius;
uniform float u_gradient;
uniform float u_alphaMultiplier;

void main()
{
    vec2 pixel = gl_FragCoord.xy;
    float dist = distance(pixel, u_center);

    float alpha = 1.0;
    if (dist < u_radius)
        alpha = 0.0;
    else if (dist < u_radius + u_gradient)
        alpha = (dist - u_radius) / u_gradient;

    alpha *= u_alphaMultiplier;

    gl_FragColor = vec4(0.0, 0.0, 0.0, alpha);
}
