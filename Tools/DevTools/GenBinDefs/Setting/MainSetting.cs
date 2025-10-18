using System.Text.Json.Serialization;

namespace GenBinDefs.Setting
{
    public class MainSetting
    {
        public MainSetting()
        {
            Langs = new List<LangSetting>();
            Font = "Roboto; 10,2";
        }

        [JsonRequired]
        [JsonPropertyName("font")]
        public required string Font { get; set; }

        [JsonRequired]
        [JsonPropertyName("langs")]
        public required IList<LangSetting> Langs { get; set; }

    }
}
