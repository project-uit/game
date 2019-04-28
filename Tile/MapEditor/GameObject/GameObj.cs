using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapEditor.GameObject
{
    public enum TypeObj
    {
        PhiTieuObj = 001,
        obj2 = 002,
    }

    class GameObj
    {
        public int Id;
        public Rectangle bounds;
        public TypeObj Type;
        public Image Image;

        public GameObj(int id, Rectangle bounds, TypeObj type, Image image)
        {
            this.Id = id;
            this.bounds = bounds;
            this.Type = type;
            this.Image = image;
        }
    }
}
