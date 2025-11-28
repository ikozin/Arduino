using System.Text.Json.Serialization;

namespace FontCostructor.Setting
{
    public class MainSetting
    {
        public MainSetting()
        {
            Font = "Roboto; 10,2";
            Patterns = new List<PatternItem>();
            Langs = new List<LangSetting>();
        }

        [JsonRequired]
        [JsonPropertyName("font")]
        public required string Font { get; set; }

        [JsonRequired]
        [JsonPropertyName("patterns")]
        public IList<PatternItem> Patterns { get; set; }

        [JsonRequired]
        [JsonPropertyName("langs")]
        public IList<LangSetting> Langs { get; set; }
    }
}
