using Laba6.Common;
using OpenTK.Graphics.OpenGL4;
using OpenTK.Mathematics;
using OpenTK.Windowing.Common;
using OpenTK.Windowing.GraphicsLibraryFramework;
using OpenTK.Windowing.Desktop;
using Keys = OpenTK.Windowing.GraphicsLibraryFramework.Keys;
using ImGuiNET;

namespace Laba6
{
    public class Window : GameWindow
    {
        // Вершины квадратов
        private readonly float[] _vertices =
        {
            // Позиции          Нормали              Текстурные координаты
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
        };

        //Класс пуль
        public class bullet
        {
            public Vector3 pos;
            public Vector3 forward;
        }

        // Список позиций кубов, составляющих пол, стены и потолок
        List<Vector3> _cubePositions = new List<Vector3>();

        // Список выстреленных пуль
        private List<bullet> redCubes = new List<bullet>();

        // Список позиций оранжевых прямоугольников (врагов)
        private List<Vector3> orangeCubes = new List<Vector3>()
        {
            new Vector3(-1.4f, 0.0f, 0.0f),
            new Vector3(2.4f, 0.0f, 0.0f),
            new Vector3(2.0f, 0.0f, 1.4f),
            new Vector3(2.0f, 0.0f, -1.4f),
            new Vector3(-2.4f, 0.0f, -3.0f),
            new Vector3(-2.0f, 0.0f, -5.4f)
        };

        // Позиции точечных светильников
        private readonly Vector3[] _pointLightPositions =
        {
            new Vector3(0.0f, 0.5f, -12.0f),
            new Vector3(2.0f, 0.5f, 0.0f),
            new Vector3(-2.0f, 0.5f, -3.0f),
            new Vector3(0.0f, 0.5f, -3.0f)
        };
        
        // Буффер VBO
        private int _vertexBufferObject;

        // VAO моделей
        private int _vaoModel;

        // VAO ламп
        private int _vaoLamp;

        // Шейдер ламп
        private Shader _lampShader;

        // Щейдер оосвещения
        private Shader _lightingShader;

        // Текстуры
        private Texture _diffuseMap;

        // Текстуры
        private Texture _specularMap;

        // Камера
        private Camera _camera;

        // Переменная дял корректного отображения камеры при первом запуске окна
        private bool _firstMove = true;

        // Позиция камеры в предыдущий кадр
        private Vector2 _lastPos;

        // Контроллер интерфейса
        private ImGuiController _controller;

        // Счётчик убийств врагов
        private int count = 0;

        private float _fps;


        public Window(GameWindowSettings gameWindowSettings, NativeWindowSettings nativeWindowSettings)
            : base(gameWindowSettings, nativeWindowSettings) { }



        // Метод срабатывающий при загрузке окна
        protected override void OnLoad()
        {
            base.OnLoad();
            
            GL.ClearColor(0f, 0f, 0f, 1.0f);

            // Создание контроллера интерфейса
            _controller = new ImGuiController(Size.X, Size.Y);

            // Создаем пол карты
            for (int j = -50; j < 50; j++)
            {
                for (int i = -50; i < 50; i++)
                {
                    float x = i;
                    float y = -1f;
                    float z = j;

                    _cubePositions.Add(new Vector3(x, y, z));
                };
            };

            // Создаём стены и потолок
            DungeonCreation();

            //Включаем корректную отрисовку 3D объектов
            GL.Enable(EnableCap.DepthTest);

            // Создаём VBO
            _vertexBufferObject = GL.GenBuffer();
            GL.BindBuffer(BufferTarget.ArrayBuffer, _vertexBufferObject);
            GL.BufferData(BufferTarget.ArrayBuffer, _vertices.Length * sizeof(float), _vertices, BufferUsageHint.StaticDraw);

            // Загружаем шейдеры
            _lightingShader = new Shader("A:\\mai_stuff\\Computer_graphics\\Laba6\\Shaders\\shader.vert", "A:\\mai_stuff\\Computer_graphics\\Laba6\\Shaders\\lighting.frag");
            _lampShader = new Shader("A:\\mai_stuff\\Computer_graphics\\Laba6\\Shaders\\shader.vert", "A:\\mai_stuff\\Computer_graphics\\Laba6\\Shaders\\shader.frag");
            
            // Создаём массив вершин моделей
            {
                _vaoModel = GL.GenVertexArray();
                GL.BindVertexArray(_vaoModel);

                var positionLocation = _lightingShader.GetAttribLocation("aPos");
                GL.EnableVertexAttribArray(positionLocation);
                GL.VertexAttribPointer(positionLocation, 3, VertexAttribPointerType.Float, false, 8 * sizeof(float), 0);

                var normalLocation = _lightingShader.GetAttribLocation("aNormal");
                GL.EnableVertexAttribArray(normalLocation);
                GL.VertexAttribPointer(normalLocation, 3, VertexAttribPointerType.Float, false, 8 * sizeof(float), 3 * sizeof(float));

                var texCoordLocation = _lightingShader.GetAttribLocation("aTexCoords");
                GL.EnableVertexAttribArray(texCoordLocation);
                GL.VertexAttribPointer(texCoordLocation, 2, VertexAttribPointerType.Float, false, 8 * sizeof(float), 6 * sizeof(float));
            }

            // Создаём массив вершшин ламп
            {
                _vaoLamp = GL.GenVertexArray();
                GL.BindVertexArray(_vaoLamp);

                var positionLocation = _lampShader.GetAttribLocation("aPos");
                GL.EnableVertexAttribArray(positionLocation);
                GL.VertexAttribPointer(positionLocation, 3, VertexAttribPointerType.Float, false, 8 * sizeof(float), 0);
            }

            // Загрузка текстур
            _diffuseMap = Texture.LoadFromFile("A:\\mai_stuff\\Computer_graphics\\Laba6\\Resources\\floor.png");
            _specularMap = Texture.LoadFromFile("A:\\mai_stuff\\Computer_graphics\\Laba6\\Resources\\floor.png");

            // Создание класса камеры
            _camera = new Camera(Vector3.UnitZ * 3, Size.X / (float)Size.Y);

            // Не даём курсору покинуть пределы окна и скрываем его
            CursorState = CursorState.Grabbed; 
        }



        // Метод срабатывающий при обновлении окна
        protected override void OnUpdateFrame(FrameEventArgs e)
        {
            base.OnUpdateFrame(e);
            
            _fps = 1.0f / (float)e.Time;

            // Проверяем активно ли окно
            if (!IsFocused)
            {
                return;
            }
            

            // Получаем нажатые клавиши клавиатуры
            var input = KeyboardState;

            // Если нажата кнопка Escape - закрываем окно
            if (input.IsKeyDown(Keys.Escape))
            {
                Close();
            }

            const float cameraSpeed = 1.5f; // Скорость движения камеры
            const float sensitivity = 0.1f; // Чувствительность камеры

            // Получаем плоское направление (X, Z)
            Vector3 flatFront = new Vector3(_camera.Front.X, 0, _camera.Front.Z).Normalized();
            Vector3 flatRight = new Vector3(_camera.Right.X, 0, _camera.Right.Z).Normalized();

            if (input.IsKeyDown(Keys.W)) // При нажатии W двигаемся вперёд, если нет столкновения с стеной
            {
                Vector3 newPos = _camera.Position + flatFront * cameraSpeed * (float)e.Time;
                if (!PlayerCollision(newPos))
                    _camera.Position += flatFront * cameraSpeed * (float)e.Time; 
            }
            if (input.IsKeyDown(Keys.S)) // При нажатии S двигаемся назад, если нет столкновения с стеной
            {
                Vector3 newPos = _camera.Position - flatFront * cameraSpeed * (float)e.Time;
                if (!PlayerCollision(newPos))
                    _camera.Position -= flatFront * cameraSpeed * (float)e.Time;
            }
            if (input.IsKeyDown(Keys.A)) // При нажатии A двигаемся влево, если нет столкновения с стеной
            {
                Vector3 newPos = _camera.Position - flatRight * cameraSpeed * (float)e.Time;
                if (!PlayerCollision(newPos))
                    _camera.Position -= flatRight * cameraSpeed * (float)e.Time;
            }
            if (input.IsKeyDown(Keys.D)) // При нажатии D двигаемся вправо, если нет столкновения с стеной
            {
                Vector3 newPos = _camera.Position + flatRight * cameraSpeed * (float)e.Time;
                if (!PlayerCollision(newPos))
                    _camera.Position += flatRight * cameraSpeed * (float)e.Time;
            }


            // Получаем состояние мыши
            var mouse = MouseState;

            // Если нажали на левую кнопку мыши, то добавляем в список снарядов новую пулю, задаёи позицию спавна как 
            // позицию камеры и ставим вектор направления на вектор, куда смотрит камера
            if (mouse.IsButtonPressed(MouseButton.Left))
            {
                bullet shot = new bullet();
                shot.pos = _camera.Position;
                shot.forward = new Vector3(_camera.Front.X, 0, _camera.Front.Z).Normalized();
                redCubes.Add(shot);
            }

            // Проверяем если пуля столкнулась со стеной, полом или потолком, то она уничтожается
            for (int i = 0; i < redCubes.Count; i++)
            {
                // Рассчитываем скорость пуль учитывая скорость, направление и время прошедшее с последнего кадра
                redCubes[i].pos += redCubes[i].forward * 5f * (float)e.Time;

                for (int j = 0; j < _cubePositions.Count; j++)
                {
                    if (new Vector3((float)Math.Round(redCubes[i].pos.X), (float)Math.Round(redCubes[i].pos.Y),
                        (float)Math.Round(redCubes[i].pos.Z)) == new Vector3((float)Math.Round(_cubePositions[j].X),
                        (float)Math.Round(_cubePositions[j].Y), (float)Math.Round(_cubePositions[j].Z)))
                    {
                        redCubes.Remove(redCubes[i]);
                        break;
                    }
                }
            }


            // Проверяем если пуля столкнулась с врагом (оранжевым прямоугольником), то они оба уничтожаются, а к
            // счётчику убийств прибавляется 1
            for (int i = 0; i < redCubes.Count; i++)
            {
                for (int k = 0; k < orangeCubes.Count; k++)
                {

                    if (new Vector3((float)Math.Round(redCubes[i].pos.X), (float)Math.Round(redCubes[i].pos.Y),
                            (float)Math.Round(redCubes[i].pos.Z)) == new Vector3((float)Math.Round(orangeCubes[k].X),
                            (float)Math.Round(orangeCubes[k].Y), (float)Math.Round(orangeCubes[k].Z)))
                    {
                        redCubes.Remove(redCubes[i]);
                        orangeCubes.Remove(orangeCubes[k]);
                        count++;
                        break;
                    }
                }
            }

            // Меняем положение камеры и проверяем чтобы не было странных движений, если мы только запустили окно
            if (_firstMove)
            {
                _lastPos = new Vector2(mouse.X, mouse.Y);
                _firstMove = false;
            }
            else
            {
                var deltaX = mouse.X - _lastPos.X;
                var deltaY = mouse.Y - _lastPos.Y;
                _lastPos = new Vector2(mouse.X, mouse.Y);

                _camera.Yaw += deltaX * sensitivity;
                _camera.Pitch -= deltaY * sensitivity;
            }
        }



        // Метод срабатывающий при рендеринге окна
        protected override void OnRenderFrame(FrameEventArgs e)
        {
            base.OnRenderFrame(e);

            // Обновляем кадр интерфейса
            _controller.Update(this, (float)e.Time);

            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);

            GL.BindVertexArray(_vaoModel);

            // Используем текстуры для освещения
            _diffuseMap.Use(TextureUnit.Texture0);
            _specularMap.Use(TextureUnit.Texture1);
            _lightingShader.Use();

            // Передаём в шейдеры матрицы вида и проэкции камеры
            _lightingShader.SetMatrix4("view", _camera.GetViewMatrix());
            _lightingShader.SetMatrix4("projection", _camera.GetProjectionMatrix());

            // Передаём в позицию камеры в шейдеры
            _lightingShader.SetVector3("viewPos", _camera.Position);

            // Передача параметров в шейдеры для отрисовки освещённого материала
            _lightingShader.SetInt("material.diffuse", 0);
            _lightingShader.SetInt("material.specular", 1);
            _lightingShader.SetVector3("material.specular", new Vector3(0.5f, 0.5f, 0.5f));
            _lightingShader.SetFloat("material.shininess", 32.0f);


            // Направленный свет
            _lightingShader.SetVector3("dirLight.direction", new Vector3(-0.2f, -1.0f, -0.3f));
            _lightingShader.SetVector3("dirLight.ambient", new Vector3(0.05f, 0.05f, 0.05f));
            _lightingShader.SetVector3("dirLight.diffuse", new Vector3(0.4f, 0.4f, 0.4f));
            _lightingShader.SetVector3("dirLight.specular", new Vector3(0.5f, 0.5f, 0.5f));

            // Точечный свет pointLights
            for (int i = 0; i < _pointLightPositions.Length; i++)
            {
                _lightingShader.SetVector3($"pointLights[{i}].position", _pointLightPositions[i]);
                _lightingShader.SetVector3($"pointLights[{i}].ambient", new Vector3(0.05f, 0.05f, 0.05f));
                _lightingShader.SetVector3($"pointLights[{i}].diffuse", new Vector3(0.8f, 0.8f, 0.8f));
                _lightingShader.SetVector3($"pointLights[{i}].specular", new Vector3(1.0f, 1.0f, 1.0f));
                _lightingShader.SetFloat($"pointLights[{i}].constant", 3.0f);
                _lightingShader.SetFloat($"pointLights[{i}].linear", 0.09f);
                _lightingShader.SetFloat($"pointLights[{i}].quadratic", 0.032f);
            }

            // Прожекторы
            _lightingShader.SetVector3("spotLight.ambient", new Vector3(0.0f, 0.0f, 0.0f));
            _lightingShader.SetVector3("spotLight.diffuse", new Vector3(1.0f, 1.0f, 1.0f));
            _lightingShader.SetVector3("spotLight.specular", new Vector3(1.0f, 1.0f, 1.0f));
            _lightingShader.SetFloat("spotLight.constant", 1.0f);
            _lightingShader.SetFloat("spotLight.linear", 0.09f);
            _lightingShader.SetFloat("spotLight.quadratic", 0.032f);
            _lightingShader.SetFloat("spotLight.cutOff", MathF.Cos(MathHelper.DegreesToRadians(12.5f)));
            _lightingShader.SetFloat("spotLight.outerCutOff", MathF.Cos(MathHelper.DegreesToRadians(17.5f)));



            // Режим рендера  0 - текстура окружения
            _lightingShader.SetInt("renderMode", 0);
            // Рендерим кубы
            for (int i = 0; i < _cubePositions.Count; i++)
            {
                // Матрицы трансформаций (положение)
                Matrix4 model = Matrix4.CreateTranslation(_cubePositions[i]);
                _lightingShader.SetMatrix4("model", model);

                GL.DrawArrays(PrimitiveType.Triangles, 0, 36);
            }

            // Режим рендера  1 - красный цвет пуль
            // Рендерим пули
            _lightingShader.SetInt("renderMode", 1);
            for (int i = 0; i < redCubes.Count; i++)
            {
                // Матрицы трансформаций (размер и положение)
                Matrix4 model = Matrix4.CreateScale(0.05f) * Matrix4.CreateTranslation(redCubes[i].pos);
                _lightingShader.SetMatrix4("model", model);

                GL.DrawArrays(PrimitiveType.Triangles, 0, 36);
            }

            // Режим рендера  2 - оранжевый цвет врагов
            // Рендерим врагов
            _lightingShader.SetInt("renderMode", 2);
            for (int i = 0; i < orangeCubes.Count; i++)
            {
                // Матрицы трансформаций (размер и положение)
                Matrix4 model = Matrix4.CreateScale(0.2f, 0.5f, 0.2f) * Matrix4.CreateTranslation(orangeCubes[i]);
                _lightingShader.SetMatrix4("model", model);

                GL.DrawArrays(PrimitiveType.Triangles, 0, 36);
            }

            GL.BindVertexArray(_vaoLamp);

            _lampShader.Use();

            _lampShader.SetMatrix4("view", _camera.GetViewMatrix());
            _lampShader.SetMatrix4("projection", _camera.GetProjectionMatrix());

            // Рисуем все pointLights в нужном положении
            for (int i = 0; i < _pointLightPositions.Length; i++)
            {
                Matrix4 lampMatrix = Matrix4.CreateScale(0.2f);
                lampMatrix = lampMatrix * Matrix4.CreateTranslation(_pointLightPositions[i]);

                _lampShader.SetMatrix4("model", lampMatrix);

                GL.DrawArrays(PrimitiveType.Triangles, 0, 36);
            }


            // Отображение количества убитых врагов в интерфейсе
            ImGui.Begin("Stats"); // Начинаем блок интерфейса с названием "Stats"
            ImGui.Text($"FPS: {Math.Round(_fps, 2)}"); // Отображаем FPS с округлением до двух знаков
            ImGui.Text("Enemies killed: " + count.ToString()); // Отображаем количество убитых врагов
            ImGui.End(); // Завершаем блок интерфейса
            _controller.Render();
            
            

            SwapBuffers();
        }



        // На колёсико мышки увеличиваем или уменьшаем угло обзора
        protected override void OnMouseWheel(MouseWheelEventArgs e)
        {
            base.OnMouseWheel(e);

            _camera.Fov -= e.OffsetY;
        }



        // Метод не позволяет картинке искажаться при изменении размера окна
        protected override void OnResize(ResizeEventArgs e)
        {
            base.OnResize(e);

            GL.Viewport(0, 0, Size.X, Size.Y);
            _camera.AspectRatio = Size.X / (float)Size.Y;
        }




        // Создание позиций кубов для стен и потолка
        private void DungeonCreation()
        {
            _cubePositions.Add(new Vector3(1f, 0f, 3f));
            _cubePositions.Add(new Vector3(0f, 0f, 4f));
            _cubePositions.Add(new Vector3(-1f, 0f, 3f));
            _cubePositions.Add(new Vector3(-1f, 0f, 2f));
            _cubePositions.Add(new Vector3(1f, 0f, 2f));
            _cubePositions.Add(new Vector3(1f, 0f, 1f));
            _cubePositions.Add(new Vector3(3f, 0f, 1f));
            _cubePositions.Add(new Vector3(2f, 0f, 2f));
            _cubePositions.Add(new Vector3(3f, 0f, 0f));
            _cubePositions.Add(new Vector3(3f, 0f, -1f));
            _cubePositions.Add(new Vector3(1f, 0f, -1f));
            _cubePositions.Add(new Vector3(2f, 0f, -2f));
            _cubePositions.Add(new Vector3(-1f, 0f, 1f));
            _cubePositions.Add(new Vector3(-2f, 0f, 0f));
            _cubePositions.Add(new Vector3(-1f, 0f, -1f));
            _cubePositions.Add(new Vector3(1f, 0f, -1f));
            _cubePositions.Add(new Vector3(-1f, 0f, -2f));
            _cubePositions.Add(new Vector3(1f, 0f, -2f));
            _cubePositions.Add(new Vector3(1f, 0f, -3f));
            _cubePositions.Add(new Vector3(-1f, 0f, -4f));
            _cubePositions.Add(new Vector3(0f, 0f, -4f));
            _cubePositions.Add(new Vector3(-3f, 0f, -3f));
            _cubePositions.Add(new Vector3(-1f, 1f, -3f));
            _cubePositions.Add(new Vector3(-3f, 0f, -4f));
            _cubePositions.Add(new Vector3(-3f, 0f, -5f));
            _cubePositions.Add(new Vector3(-2f, 0f, -6f));
            _cubePositions.Add(new Vector3(-1f, 0f, -5f));
            _cubePositions.Add(new Vector3(-1f, 0f, -4f));
            _cubePositions.Add(new Vector3(-2f, 0f, -2f));
            _cubePositions.Add(new Vector3(-2f, 1f, -4f));
            _cubePositions.Add(new Vector3(-2f, 1f, -5f));
            _cubePositions.Add(new Vector3(-2f, 1f, -3f));
            _cubePositions.Add(new Vector3(0f, 1f, 1f));
            _cubePositions.Add(new Vector3(0f, 1f, 2f));
            _cubePositions.Add(new Vector3(0f, 1f, 3f));
            _cubePositions.Add(new Vector3(-1f, 1f, 0f));
            _cubePositions.Add(new Vector3(1f, 1f, 0f));
            _cubePositions.Add(new Vector3(2f, 1f, 0f));
            _cubePositions.Add(new Vector3(2f, 1f, -1f));
            _cubePositions.Add(new Vector3(2f, 1f, 1f));
            _cubePositions.Add(new Vector3(0f, 1f, 0f));
            _cubePositions.Add(new Vector3(0f, 1f, -1f));
            _cubePositions.Add(new Vector3(0f, 1f, -2f));
            _cubePositions.Add(new Vector3(0f, 1f, -3f));
        }



        // Проверка столкновения камеры с стенами (не даём проходить камере сквозь стены)
        private bool PlayerCollision(Vector3 newPos)
        {
            for (int i = 0; i < _cubePositions.Count; i++)
            {
                // Если округлённая позиция камеры совпадвает с позицией стены, то не даём пройти
                if(new Vector3((float)Math.Round(newPos.X), (float)Math.Round(newPos.Y),
                        (float)Math.Round(newPos.Z)) == new Vector3((float)Math.Round(_cubePositions[i].X),
                        (float)Math.Round(_cubePositions[i].Y), (float)Math.Round(_cubePositions[i].Z)))
                {
                    return true;
                }
            }

            return false;
        }
    }
}
