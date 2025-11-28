using System.Text.Json.Serialization;

namespace FontCostructor.Setting
{
    public class PatternItem
    {

        [JsonRequired]
        [JsonPropertyName("name")]
        public required string Name { get; set; }

        [JsonRequired]
        [JsonPropertyName("value")]
        public required string Value { get; set; }

        public override string ToString()
        {
            return Name.ToString();
        }
    }
}
