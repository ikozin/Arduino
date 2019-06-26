public interface IGameEngine
{
  void start();
  void stop();
  void draw();
  void keyEvent(KeyEvent keyEvent);
  void mouseEvent(MouseEvent mouseEvent);
}
