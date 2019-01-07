class TPoint
{
  int X;
  int Y;
  
  TPoint(int x, int y)
  {
    X = x;
    Y = y;
  }
    
  TPoint plus (TPoint other)
  {
    if (null == other) return null;
    return new TPoint(this.X + other.X, this.Y + other.Y);
  }

  TPoint minus (TPoint other)
  {
    if (null == other) return null;
    return new TPoint(this.X - other.X, this.Y - other.Y);
  }
}
