
using ConsoleApp;
namespace ConsoleApp.Test;

public class UnitTest1
{
    [Fact]
    public void Test_StringUtils_Reversed()
    {
        var testStr = "hello";
        var reversed = StringUtils.Reversed(testStr );
        Assert.Equal("olleh",reversed);
    }
}