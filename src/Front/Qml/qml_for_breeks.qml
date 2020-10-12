import QtQuick 2.3
import QtGraphicalEffects 1.12

Item
{
    id: breek

    property variant emojies:
    [
        "qrc:/Images/Front/Images/Breeks/1.png",
        "qrc:/Images/Front/Images/Breeks/2.png",
        "qrc:/Images/Front/Images/Breeks/3.png",
        "qrc:/Images/Front/Images/Breeks/4.png",
        "qrc:/Images/Front/Images/Breeks/5.png",
        "qrc:/Images/Front/Images/Breeks/6.png",
        "qrc:/Images/Front/Images/Breeks/7.png",
        "qrc:/Images/Front/Images/Breeks/8.png",
        "qrc:/Images/Front/Images/Breeks/9.png",
        "qrc:/Images/Front/Images/Breeks/10.png"
    ]
    property int indexOfEmoji

    property variant conditions:
    [
        "#FF3366", // red
        "#ECEAEC", // grey - foreground
        "#ECEAEC", // grey - background
        "#66FF66"  // green
    ]
    property int indexOfCondFrom
    property int indexOfCondTo

    property bool animationOn // включить / отключить анимацию - если хочется смотреть только на один breek
    property int direction // 1 - поворот вверх, 0 - поворот вниз

    // назначается вручную
    property int pushButtonWidth: 80
    property int pushButtonHeight: 80
    property var sceneWidth: 0.875 * pushButtonWidth
    property var sceneHeight: 0.875 * pushButtonHeight
    property var offset: 0.1
    property var breekWidth: getBreekSide("width")
    property var breekHeight: getBreekSide("height")

    /* изменение ширины уезжающего кубика(чтобы не было козырька справа) */
    property var offsetWidthLeave: getOffset(10, breekWidth, image.implicitWidth)

    property var rotationUpDuration: 500
    property var rotationDownDuration: 700
    property var borderWidth: 0.01 // убрал границу прямоугольников
    property var radiuS: 10 // радиус закругления прямоугольников в углах

    /* пропорции для уменьшения "козырька" */
    property var proportion1: 0.01 // 0.01
    property var proportion2: 0.15 // 0.15
    property var proportion3: 0.28 // 0.28
    property var proportion4: 0.56 // 0.56

    property var a: 3
    property var offsetHeightA: getOffset(a, breekHeight, image.implicitHeight)
    property var b: 17
    property var offsetHeightB: getOffset(b, breekHeight, image.implicitHeight)
    property var c: 38
    property var offsetHeightC: getOffset(c, breekHeight, image.implicitHeight)
    property var d: 40
    property var offsetHeightD: getOffset(d, breekHeight, image.implicitHeight)

    /* переменные для уменьшения "козырька" */
    property var shrinkDur1: (direction ? rotationUpDuration : rotationDownDuration) * proportion1
    property var shrinkDur2: (direction ? rotationUpDuration : rotationDownDuration) * proportion2
    property var shrinkDur3: (direction ? rotationUpDuration : rotationDownDuration) * proportion3
    property var shrinkDur4: (direction ? rotationUpDuration : rotationDownDuration) * proportion4

    function getOffset(absolute, breekSideLength, imageImplic)
    {
        return absolute * (breekSideLength / imageImplic)
    }

    function getCondShadeOffset(sideLength)
    {
        return 2 * (sideLength / 53.03030303)
        // 53.03030303 = old breekWidth or breekHeight
    }

    function getEmojiShadeOffset(sideLength)
    {
        return 1 * (sideLength / 53.03030303)
        // 53.03030303 = old breekWidth or breekHeight
    }

    function getBreekSide(flag)
    {
        if (flag === "width") {
            return sceneWidth / ((1 + offset)*(1 + 2*offset))
        }

        if (flag === "height") {
            return sceneHeight / ((1 + offset)*(1 + 2*offset))
        }
    }

    function getXCondPosition(sideLength)
    {
        return offset * sideLength*(2 + offset)
        // offset * ((1 + offset)*sideLength) + offset * sideLength
    }

    function getYCondPosition(sideLength)
    {
        return offset * ((1 + offset)*sideLength)
    }

    function getXEmojiPosition(sideLength)
    {
        return offset * ((1 + offset)*sideLength)
    }

    function getYEmojiPosition(sideLength)
    {
        return offset * sideLength*(2 + offset)
        // offset * ((1 + offset)*sideLength) + offset * sideLength
    }

    opacity: 1.0
    layer.enabled: true


    /* объявление цветных и эмодзи квадратов */
    /* предполагается, что размеры Image картинки(эмодзи) изначально совпадают
       с размерами Rectangle квадратов и соответствуют breekHeight и breekWidth */
    Rectangle
    {
        id: conditionFrom

        property alias icon: image.source

        color: conditions[indexOfCondFrom]

        radius: radiuS

        // координаты прямоугольника в окне
        x: getXCondPosition(breekWidth)
        y: getYCondPosition(breekHeight)

        // не забывай про то, что в анимации идёт расчёт на то,
        // что Rectangle.width == breekWidth и Rectangle.height == breekHeight
        width: breekWidth
        height: breekHeight

        border.width: borderWidth

        transform: Rotation {
            id: rotFromCond;

            origin.x: 0
            origin.y: 0
            axis { x: 1; y: 0; z: 0 }
            angle: 0
        }

        // работа с тенью
        layer.enabled: true
        layer.effect: DropShadow
        {
            anchors.fill: conditionFrom
            radius: 16.0
            samples: 33
            spread: 0
            color: "darkgray"
            transparentBorder: true
            horizontalOffset: getCondShadeOffset(breekWidth)
            verticalOffset: getCondShadeOffset(breekHeight)
        }
    }
    Rectangle
    {
        id: emojiFrom

        property alias icon: image

        radius: radiuS

        // координаты эмодзи относительно прямоугольника(их размеры идентичны, согласно размеру исходной *.png)
        x: getXEmojiPosition(breekWidth)
        y: getYEmojiPosition(breekHeight)

        // не забывай про то, что в анимации идёт расчёт на то,
        // что Rectangle.width == breekWidth и Rectangle.height == breekHeight
        width: breekWidth
        height: breekHeight

        border.width: borderWidth

        transform: Rotation {
            id: rotFromEmoj

            origin.x: 0
            origin.y: 0
            axis { x: 1; y: 0; z: 0 }
            angle: 0
        }

        // работа с тенью
        layer.enabled: true
        layer.effect: DropShadow
        {
            anchors.fill: emojiFrom
            radius: 16.0
            samples: 33
            spread: 0
            color: "darkgray"
            transparentBorder: true
            horizontalOffset: getEmojiShadeOffset(breekWidth)
            verticalOffset: getEmojiShadeOffset(breekHeight)
        }

        Image {
            id: image
            source: emojies[indexOfEmoji]
            width: breekWidth
            height: breekHeight
        }
    }
    Rectangle
    {
        id: conditionTo

        property alias icon: image.source

        color: conditions[indexOfCondTo]

        radius: radiuS

        // координаты прямоугольника в окне
        x: getXCondPosition(breekWidth)
        y: getYCondPosition(breekHeight)

        // не забывай про то, что в анимации идёт расчёт на то,
        // что Rectangle.width == breekWidth и Rectangle.height == breekHeight
        width: breekWidth
        height: breekHeight

        border.width: borderWidth

        transform: Rotation {
            id: rotToCond

            origin.x: 0
            origin.y: 0
            axis { x: 1; y: 0; z: 0 }
            angle: direction ? -90 : 90
        }

        // работа с тенью
        layer.enabled: true
        layer.effect: DropShadow
        {
            anchors.fill: conditionTo
            radius: 16.0
            samples: 33
            spread: 0
            color: "darkgray"
            transparentBorder: true
            horizontalOffset: getCondShadeOffset(breekWidth)
            verticalOffset: getCondShadeOffset(breekHeight)
        }
    }
    /* 1 - 333, 2 - dark, 3 - dark + 16 */
    Rectangle
    {
        id: emojiTo

        property alias icon: image

        radius: radiuS

        // координаты эмодзи относительно прямоугольника(их размеры идентичны, согласно размеру исходной *.png)
        x: getXEmojiPosition(breekWidth)
        y: getYEmojiPosition(breekHeight)

        // не забывай про то, что в анимации идёт расчёт на то,
        // что Rectangle.width == breekWidth и Rectangle.height == breekHeight
        width: breekWidth
        height: breekHeight

        border.width: borderWidth

        transform: Rotation {
            id: rotToEmoj

            origin.x: 0
            origin.y: 0
            axis { x: 1; y: 0; z: 0 }
            angle: direction ? -90 : 90
        }

        // работа с тенью
        layer.enabled: true
        layer.effect: DropShadow
        {
            anchors.fill: emojiTo
            radius: 16.0
            samples: 33
            spread: 0
            color: "darkgray"
            transparentBorder: true
            horizontalOffset: getEmojiShadeOffset(breekWidth)
            verticalOffset: getEmojiShadeOffset(breekHeight)
        }

        Image {
            id: imageAppearing
            source: emojies[indexOfEmoji]
            width: breekWidth
            height: breekHeight
        }
    }
    /* конец объявления цветных и эмодзи квадратов */

    /* блок анимации */
    ParallelAnimation
    {
        running: animationOn

        /* сама прокрутка(вокруг статичной оси) */
        NumberAnimation {
            target: rotFromCond;
            property: "angle";
            from: 0; to: direction ? 90 : -90;
            duration: (direction ? rotationUpDuration : rotationDownDuration);
        }
        NumberAnimation {
            target: rotFromEmoj;
            property: "angle";
            from: 0; to: direction ? 90 : -90;
            duration: (direction ? rotationUpDuration : rotationDownDuration);
        }
        NumberAnimation {
            target: rotToCond;
            property: "angle";
            from: direction ? -90 : 90; to: 0;
            duration: (direction ? rotationUpDuration : rotationDownDuration);
        }
        NumberAnimation {
            target: rotToEmoj;
            property: "angle";
            from: direction ? -90 : 90; to: 0;
            duration: (direction ? rotationUpDuration : rotationDownDuration);
        }
        /* конец самой прокрутки(вокруг статичной оси) */

        /* смещение точки отрисовки кубика
           (direction = true: который появляется из под низу - для эмитации "выезжания")
           (direction = false: который уезжает вниз - для эмитации "уезжания") */
        NumberAnimation {
            target: direction ? conditionTo        : conditionFrom;
            property: "y";
            from:   direction ? getYCondPosition(breekHeight) + breekHeight : getYCondPosition(breekHeight);
            to:     direction ? getYCondPosition(breekHeight)               : getYCondPosition(breekHeight) + breekHeight;
            duration: (direction ? rotationUpDuration : rotationDownDuration);
        }
        NumberAnimation {
            target: direction ? emojiTo : emojiFrom;
            property: "y";
            from:   direction ? getYEmojiPosition(breekHeight) + breekHeight : getYEmojiPosition(breekHeight);
            to:     direction ? getYEmojiPosition(breekHeight)               : getYEmojiPosition(breekHeight) + breekHeight;
            duration: (direction ? rotationUpDuration : rotationDownDuration);
        }

        // костыль для устранения бага "исчезновения" грани при повороте наверх после поворота вниз
        // включается только когда direction = true, то есть поворот - наверх
        NumberAnimation {
            target: conditionFrom
            property: "y"
            from: getYCondPosition(breekHeight);
            to: getYCondPosition(breekHeight);
            duration: (direction ? rotationUpDuration : 0);
        }
        NumberAnimation {
            target: emojiFrom
            property: "y"
            from: getYEmojiPosition(breekHeight);
            to: getYEmojiPosition(breekHeight);
            duration: (direction ? rotationUpDuration : 0);
        }
        /* конец смещения точки отрисовки кубика
           (direction = true: который появляется из под низу - для эмитации "выезжания")
           (direction = false: который уезжает вниз - для эмитации "уезжания") */


        /* работа с размерами(высота) кубиков для устранения "козырька"/"щели" */
        /* блок последовательной анимации */
        SequentialAnimation
        {
            ParallelAnimation
            {
                NumberAnimation {
                    target: conditionFrom;
                    property: "height";
                    from: breekHeight;
                    to:   breekHeight - offsetHeightA;
                    duration: shrinkDur1;
                }
                NumberAnimation {
                    target: emojiFrom;
                    property: "height";
                    from: breekHeight;
                    to:   breekHeight - offsetHeightA;
                    duration: shrinkDur1;
                }
            }
            ParallelAnimation
            {
                NumberAnimation {
                    target: conditionFrom;
                    property: "height";
                    from: breekHeight - offsetHeightA;
                    to:   breekHeight - offsetHeightB;
                    duration: shrinkDur2;
                }
                NumberAnimation
                {
                    target: emojiFrom;
                    property: "height";
                    from: breekHeight - offsetHeightA;
                    to:   breekHeight - offsetHeightB;
                    duration: shrinkDur2;
                }
            }
            ParallelAnimation
            {
                NumberAnimation {
                    target: conditionFrom;
                    property: "height";
                    from: breekHeight - offsetHeightB;
                    to:   breekHeight - offsetHeightC;
                    duration: shrinkDur3;
                }
                NumberAnimation {
                    target: emojiFrom;
                    property: "height";
                    from: breekHeight - offsetHeightB;
                    to:   breekHeight - offsetHeightC;
                    duration: shrinkDur3;
                }
            }
            ParallelAnimation
            {
                NumberAnimation {
                    target: conditionFrom;
                    property: "height";
                    from: breekHeight - offsetHeightC;
                    to:   breekHeight - offsetHeightD;
                    duration: shrinkDur4;
                }
                NumberAnimation {
                    target: emojiFrom;
                    property: "height";
                    from: breekHeight - offsetHeightC;
                    to:   breekHeight - offsetHeightD;
                    duration: shrinkDur4;
                }
            }
        }
        /* конец блока последовательной анимации */
        /* конец работы с размерами(высота) кубиков для устранения "козырька"/"щели" */

        /* изменение ширины уезжающего кубика(чтобы не было козырька справа) */
        NumberAnimation {
            target: conditionFrom;
            property: "width";
            from: breekWidth;
            to:   breekWidth - offsetWidthLeave;
            duration: (direction ? rotationUpDuration : rotationDownDuration);
        }
        NumberAnimation {
            target: emojiFrom;
            property: "width";
            from: breekWidth;
            to:   breekWidth - offsetWidthLeave;
            duration: (direction ? rotationUpDuration : rotationDownDuration);
        }
        /* конец изменения ширины уезжающего кубика(чтобы не было козырька справа) */

        /* изменение длины уезжающего эмодзи */
        NumberAnimation {
            target: image;
            property: "height";
            from: breekHeight; to: 0;
            duration: (direction ? rotationUpDuration : rotationDownDuration);
        }
        /* конец изменения длины уезжающего эмодзи */


        /* -------- ТОЛЬКО ПРИ ПОВОРОТЕ ВНИЗ -------- */

        /* изменение длины вызжающего кубика(чтобы устранить щель) */
        ParallelAnimation
        {
            NumberAnimation {
                target: conditionTo;
                property: "height";
                from: 0; to: breekHeight;
                duration: direction ? 0 : (direction ? rotationUpDuration : rotationDownDuration);
            }
            NumberAnimation {
                target: emojiTo;
                property: "height";
                from: 0; to: breekHeight;
                duration: direction ? 0 : (direction ? rotationUpDuration : rotationDownDuration);
            }
            NumberAnimation {
                target: imageAppearing;
                property: "height";
                from: 0; to: breekHeight;
                duration: direction ? 0 : (direction ? rotationUpDuration : rotationDownDuration);
            }
        }
        /* конец изменения длины вызжающего кубика(чтобы устранить щель) */
    }
    /* конец блока анимации */
}


