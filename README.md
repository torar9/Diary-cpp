# Diary-cpp
<p>Qt C++ diary.</p>

<h2>Simple program structure:</h2>
<img src="https://github.com/torar9/Diary-cpp/blob/master/app.png">

<ul>
<li><b>Database.cpp/hpp</b> - Holds and stores data into .xml file and takes care about displaying data in QWidgetList.</li>
<li><b>DiaryWindow.cpp/hpp</b> - Main and the only window.</li>
<li><b>UserData.cpp/hpp</b> - Holds text and unique identifier which is date and random generated number in this format: "Hours:Minutes:Seconds_Day.Month.Year#Random_Number"</li>
<li><b>pugixml.cpp/hpp</b> - <a href="https://pugixml.org/">Pugixml</a> library.</li>
<li><b>pugiconfig.hpp</b> - <a href="https://pugixml.org/">Pugixml</a> config</li>
</ul>

<hr>

<h2>Used libraries/frameworks:</h2>
<ul>
<li><a href="https://pugixml.org/">pugixml 1.9</a> or newer</li>
<li><a href="http://www.boost.org/">Boost 1.67</a> or newer</li>
<li><a href="https://www.qt.io/">Qt 5.11.1</a> or newer</li>
</ul>
