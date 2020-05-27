using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TextIndex
{
    /// <summary>
    /// Класс для хранения слова и его смещения
    /// </summary>
    public class WordIndex
    {
        public string Word { get; set; }
        public List<WordOffset> RowOffset { get; set; } = new List<WordOffset>();
    }
    /// <summary>
    /// Класс для хранения индексов индексируемых файлов
    /// </summary>
    public class TextIndex
    {
        public List<FileIndex> Files { get; set; } = new List<FileIndex>();
    }
    /// <summary>
    /// Клас для хранения индексов одного файла
    /// </summary>
    public class FileIndex
    {
        public string Name { get; set; }
        public List<WordIndex> Words { get; set; } = new List<WordIndex>();
    }
    /// <summary>
    /// Класс для хранения смещения
    /// </summary>
    public class WordOffset
    {
        public int Row { get; set; }
        public int Offset { get; set; }
    }
}

