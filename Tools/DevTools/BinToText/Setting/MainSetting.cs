using System.Text.Json.Serialization;

namespace BinToText.Setting
{
    public class MainSetting
    {
        public MainSetting()
        {
            Langs = new LangSetting[0];
            Font = "Roboto; 10,2";
        }

        [JsonRequired]
        [JsonPropertyName("font")]
        public string Font { get; set; }

        [JsonRequired]
        [JsonPropertyName("langs")]
        public LangSetting[] Langs { get; set; }

    }
}
