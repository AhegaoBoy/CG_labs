#version 330 core

out vec4 FragColor;

uniform vec2 resolution; // Разрешение экрана
uniform int maxDepth;    // Максимальная глубина трассировки

// Центр сферы и её радиус
const vec3 sphereCenter = vec3(0.0, 0.0, -3.0);
const float sphereRadius = 1.0;

// Границы куба (AABB)
const vec3 cubeMin = vec3(-1.0, -1.0, -5.0);
const vec3 cubeMax = vec3(1.0, 1.0, -3.0);

// Направление луча от \"камеры\"
vec3 rayDirection(float fov, vec2 fragCoord) {
    vec2 xy = fragCoord - resolution / 2.0;
    float z = (resolution.y / 2.0) / tan(radians(fov / 2.0));
    return normalize(vec3(xy, -z));
}

// Проверка пересечения луча со сферой
bool intersectSphere(vec3 origin, vec3 dir, out float t, out vec3 normal) {
    vec3 oc = origin - sphereCenter;
    float a = dot(dir, dir);
    float b = 2.0 * dot(oc, dir);
    float c = dot(oc, oc) - sphereRadius * sphereRadius;
    float discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0) return false;

    float t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    float t2 = (-b + sqrt(discriminant)) / (2.0 * a);
    t = (t1 > 0.0) ? t1 : t2;

    if (t < 0.0) return false;

    vec3 hitPoint = origin + t * dir;    // Точка удара
    normal = normalize(hitPoint - sphereCenter);
    return true;
}

// Проверка пересечения луча с кубом (AABB)
bool intersectCube(vec3 origin, vec3 dir, out float tNear, out vec3 normal) {
    vec3 invDir = 1.0 / dir;
    vec3 t0 = (cubeMin - origin) * invDir;
    vec3 t1 = (cubeMax - origin) * invDir;

    vec3 tMin = min(t0, t1);
    vec3 tMax = max(t0, t1);

    tNear = max(max(tMin.x, tMin.y), tMin.z);
    float tFar = min(min(tMax.x, tMax.y), tMax.z);

    if (tNear > tFar || tFar < 0.0) return false;

    // Вычисляем нормаль этой грани куба
    if (tNear == t0.x) normal = vec3(-1.0, 0.0, 0.0);
    else if (tNear == t1.x) normal = vec3(1.0, 0.0, 0.0);
    else if (tNear == t0.y) normal = vec3(0.0, -1.0, 0.0);
    else if (tNear == t1.y) normal = vec3(0.0, 1.0, 0.0);
    else if (tNear == t0.z) normal = vec3(0.0, 0.0, -1.0);
    else normal = vec3(0.0, 0.0, 1.0);

    return true;
}

// Основная функция трассировки лучей
vec3 traceRay(vec3 origin, vec3 direction, int maxDepth) {
    vec3 accumulatedColor = vec3(0.0);
    vec3 currentOrigin = origin;
    vec3 currentDirection = direction;

    for (int depth = 0; depth < maxDepth; ++depth) {
        // Расстояние до объектов
        float tSphere = 1e6, tCube = 1e6;
        vec3 normalSphere, normalCube;

        // Проверяем пересечения с объектами
        bool hitSphere = intersectSphere(currentOrigin, currentDirection, tSphere, normalSphere);
        bool hitCube = intersectCube(currentOrigin, currentDirection, tCube, normalCube);

        // Если ничего не пересекли, задаем фон
        if (!hitSphere && !hitCube) {
            vec3 backgroundColor = vec3(0.1, 0.2, 0.3);
            return accumulatedColor + backgroundColor;
        }

        // Выбираем ближайшее пересечение
        float t = tSphere;
        vec3 normal = normalSphere;
        vec3 objectColor = vec3(1.0, 0.0, 0.0); // Красный цвет для сферы

        if (hitCube && (!hitSphere || tCube < tSphere)) {
            t = tCube;
            normal = normalCube;
            objectColor = vec3(0.0, 0.0, 1.0); // Синий цвет для куба
        }

        // Точка пересечения и добавление цвета объекта
        vec3 hitPoint = currentOrigin + t * currentDirection;
        accumulatedColor += objectColor / float(depth + 1);

        // Обновляем направление луча (для очередного отражения)
        currentOrigin = hitPoint + 0.001 * normal; // Смещение для предотвращения самопересечения
        currentDirection = reflect(currentDirection, normal);
    }

    return accumulatedColor;
}

// Основной вход в шейдер
void main() {
    vec3 origin = vec3(0.0, 0.0, 0.0); // Камера
    vec3 direction = rayDirection(90.0, gl_FragCoord.xy); // Луч от камеры

    vec3 color = traceRay(origin, direction, maxDepth);
    FragColor = vec4(color, 1.0);
}