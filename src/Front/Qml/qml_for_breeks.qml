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
        "#F7F7F7", // grey - foreground
        "#F7F7F7", // grey - background
        "#66FF66", // green
        "#FFFF66", // yellow
        "#666666"
    ]
    property int indexOfCondFrom
    property int indexOfCondTo

    property bool bigShadow

    property bool animationOn // включить / отключить анимацию - если хочется смотреть только на один breek
    property int direction // 1 - поворот вверх, 0 - поворот вниз

    // назначается вручную
    property int pushButtonWidth: 1.125*80 // the same as the breek->quickWidget_->width
    property int pushButtonHeight: 1.125*80 // the same as the breek->quickWidget_->height
    property var sceneWidth: pushButtonWidth
    property var sceneHeight: pushButtonHeight
    property var offset: 0.05
    property var condRectWidth: getCondSide("width")
    property var condRectHeight: getCondSide("height")
    property var condCropToCalculateEmojiSide: 0.9
    property var emojiRectWidth: getEmojiSide("width")
    property var emojiRectHeight: getEmojiSide("height")

    /* изменение ширины уезжающего кубика(чтобы не было козырька справа) */
    property var offsetWidthLeave: getOffset(10, emojiRectWidth, image.implicitWidth)

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
    property var offsetHeightA: getOffset(a, emojiRectHeight, image.implicitHeight)
    property var b: 17
    property var offsetHeightB: getOffset(b, emojiRectHeight, image.implicitHeight)
    property var c: 38
    property var offsetHeightC: getOffset(c, emojiRectHeight, image.implicitHeight)
    property var d: 40
    property var offsetHeightD: getOffset(d, emojiRectHeight, image.implicitHeight)

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

    function getCondSide(flag)
    {
        if (flag === "width") {
            return sceneWidth / ((1 + offset)*(1 + 2*offset))
        }

        if (flag === "height") {
            return sceneHeight / ((1 + offset)*(1 + 2*offset))
        }
    }

    function getEmojiSide(flag)
    {
        if (flag === "width") {
            return condRectWidth * condCropToCalculateEmojiSide
        }

        if (flag === "height") {
            return condRectHeight * condCropToCalculateEmojiSide
        }
    }

    function getXCondPosition(sideLength)
    {
//        return offset * sideLength*(2 + offset)
        // offset * ((1 + offset)*sideLength) + offset * sideLength
        return (sceneWidth - sideLength)/2
    }

    function getYCondPosition(sideLength)
    {
//        return offset * ((1 + offset)*sideLength)
        return (sceneHeight - sideLength)/2
    }

    function getXEmojiPosition(sideLength)
    {
//        return offset * ((1 + offset)*sideLength)
        return (sceneWidth - sideLength)/2
    }

    function getYEmojiPosition(sideLength)
    {
//        return offset * sideLength*(2 + offset)
        // offset * ((1 + offset)*sideLength) + offset * sideLength
        return (sceneHeight - sideLength)/2
    }

    function getColorForShadow() {
      if (bigShadow) {
        return conditions[5]
      }
      else {
        return "darkgray"
      }
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
        x: getXCondPosition(condRectWidth)
        y: getYCondPosition(condRectHeight)

        // не забывай про то, что в анимации идёт расчёт на то,
        // что Rectangle.width == condRectWidth и Rectangle.height == condRectHeight
        width: condRectWidth
        height: condRectHeight

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
            color: getColorForShadow()
            transparentBorder: true
            //horizontalOffset: getCondShadeOffset(condRectWidth)
            //verticalOffset: getCondShadeOffset(condRectHeight)
        }
    }
    Rectangle
    {
        id: emojiFrom

        property alias icon: image

        radius: radiuS

        // координаты эмодзи относительно прямоугольника(их размеры идентичны, согласно размеру исходной *.png)
        x: getXEmojiPosition(emojiRectWidth)
        y: getYEmojiPosition(emojiRectHeight)

        // не забывай про то, что в анимации идёт расчёт на то,
        // что Rectangle.width == emojiRectWidth и Rectangle.height == emojiRectHeight
        width: emojiRectWidth
        height: emojiRectHeight

        border.width: borderWidth

        transform: Rotation {
            id: rotFromEmoj

            origin.x: 0
            origin.y: 0
            axis { x: 1; y: 0; z: 0 }
            angle: 0
        }

        // работа с тенью
        /*layer.enabled: true
        layer.effect: DropShadow
        {
            anchors.fill: emojiFrom
            radius: 16.0
            samples: 33
            spread: 0
            color: "darkgray"
            transparentBorder: true
            horizontalOffset: getEmojiShadeOffset(emojiRectWidth)
            verticalOffset: getEmojiShadeOffset(emojiRectHeight)
        }*/

        Image {
            id: image
            source: emojies[indexOfEmoji]
            width: emojiRectWidth
            height: emojiRectHeight
        }
    }
    Rectangle
    {
        id: conditionTo

        property alias icon: image.source

        color: conditions[indexOfCondTo]

        radius: radiuS

        // координаты прямоугольника в окне
        x: getXCondPosition(condRectWidth)
        y: getYCondPosition(condRectHeight)

        // не забывай про то, что в анимации идёт расчёт на то,
        // что Rectangle.width == condRectWidth и Rectangle.height == condRectHeight
        width: condRectWidth
        height: condRectHeight

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
            color: getColorForShadow()

            transparentBorder: true
            //horizontalOffset: getCondShadeOffset(condRectWidth)
            //verticalOffset: getCondShadeOffset(condRectHeight)
        }
    }
    /* 1 - 333, 2 - dark, 3 - dark + 16 */
    Rectangle
    {
        id: emojiTo

        property alias icon: image

        radius: radiuS

        // координаты эмодзи относительно прямоугольника(их размеры идентичны, согласно размеру исходной *.png)
        x: getXEmojiPosition(emojiRectWidth)
        y: getYEmojiPosition(emojiRectHeight)

        // не забывай про то, что в анимации идёт расчёт на то,
        // что Rectangle.width == emojiRectWidth и Rectangle.height == emojiRectHeight
        width: emojiRectWidth
        height: emojiRectHeight

        border.width: borderWidth

        transform: Rotation {
            id: rotToEmoj

            origin.x: 0
            origin.y: 0
            axis { x: 1; y: 0; z: 0 }
            angle: direction ? -90 : 90
        }

        // работа с тенью
        /*layer.enabled: true
        layer.effect: DropShadow
        {
            anchors.fill: emojiTo
            radius: 16.0
            samples: 33
            spread: 0
            color: "darkgray"
            transparentBorder: true
            horizontalOffset: getEmojiShadeOffset(emojiRectWidth)
            verticalOffset: getEmojiShadeOffset(emojiRectHeight)
        }*/

        Image {
            id: imageAppearing
            source: emojies[indexOfEmoji]
            width: emojiRectWidth
            height: emojiRectHeight
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
            from:   direction ? getYCondPosition(condRectHeight) + condRectHeight : getYCondPosition(condRectHeight);
            to:     direction ? getYCondPosition(condRectHeight)                  : getYCondPosition(condRectHeight) + condRectHeight;
            duration: (direction ? rotationUpDuration : rotationDownDuration);
        }
        NumberAnimation {
            target: direction ? emojiTo : emojiFrom;
            property: "y";
            from:   direction ? getYEmojiPosition(emojiRectHeight) + emojiRectHeight : getYEmojiPosition(emojiRectHeight);
            to:     direction ? getYEmojiPosition(emojiRectHeight)                   : getYEmojiPosition(emojiRectHeight) + emojiRectHeight;
            duration: (direction ? rotationUpDuration : rotationDownDuration);
        }

        // костыль для устранения бага "исчезновения" грани при повороте наверх после поворота вниз
        // включается только когда direction = true, то есть поворот - наверх
        NumberAnimation {
            target: conditionFrom
            property: "y"
            from: getYCondPosition(condRectHeight);
            to: getYCondPosition(condRectHeight);
            duration: (direction ? rotationUpDuration : 0);
        }
        NumberAnimation {
            target: emojiFrom
            property: "y"
            from: getYEmojiPosition(emojiRectHeight);
            to: getYEmojiPosition(emojiRectHeight);
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
                    from: condRectHeight;
                    to:   condRectHeight - offsetHeightA;
                    duration: shrinkDur1;
                }
                NumberAnimation {
                    target: emojiFrom;
                    property: "height";
                    from: emojiRectHeight;
                    to:   emojiRectHeight - offsetHeightA;
                    duration: shrinkDur1;
                }
            }
            ParallelAnimation
            {
                NumberAnimation {
                    target: conditionFrom;
                    property: "height";
                    from: condRectHeight - offsetHeightA;
                    to:   condRectHeight - offsetHeightB;
                    duration: shrinkDur2;
                }
                NumberAnimation
                {
                    target: emojiFrom;
                    property: "height";
                    from: emojiRectHeight - offsetHeightA;
                    to:   emojiRectHeight - offsetHeightB;
                    duration: shrinkDur2;
                }
            }
            ParallelAnimation
            {
                NumberAnimation {
                    target: conditionFrom;
                    property: "height";
                    from: condRectHeight - offsetHeightB;
                    to:   condRectHeight - offsetHeightC;
                    duration: shrinkDur3;
                }
                NumberAnimation {
                    target: emojiFrom;
                    property: "height";
                    from: emojiRectHeight - offsetHeightB;
                    to:   emojiRectHeight - offsetHeightC;
                    duration: shrinkDur3;
                }
            }
            ParallelAnimation
            {
                NumberAnimation {
                    target: conditionFrom;
                    property: "height";
                    from: condRectHeight - offsetHeightC;
                    to:   condRectHeight - offsetHeightD;
                    duration: shrinkDur4;
                }
                NumberAnimation {
                    target: emojiFrom;
                    property: "height";
                    from: emojiRectHeight - offsetHeightC;
                    to:   emojiRectHeight - offsetHeightD;
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
            from: condRectWidth;
            to:   condRectWidth - offsetWidthLeave;
            duration: (direction ? rotationUpDuration : rotationDownDuration);
        }
        NumberAnimation {
            target: emojiFrom;
            property: "width";
            from: emojiRectWidth;
            to:   emojiRectWidth - offsetWidthLeave;
            duration: (direction ? rotationUpDuration : rotationDownDuration);
        }
        /* конец изменения ширины уезжающего кубика(чтобы не было козырька справа) */

        /* изменение длины уезжающего эмодзи */
        NumberAnimation {
            target: image;
            property: "height";
            from: emojiRectHeight; to: 0;
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
                from: 0; to: condRectHeight;
                duration: direction ? 0 : (direction ? rotationUpDuration : rotationDownDuration);
            }
            NumberAnimation {
                target: emojiTo;
                property: "height";
                from: 0; to: emojiRectHeight;
                duration: direction ? 0 : (direction ? rotationUpDuration : rotationDownDuration);
            }
            NumberAnimation {
                target: imageAppearing;
                property: "height";
                from: 0; to: emojiRectHeight;
                duration: direction ? 0 : (direction ? rotationUpDuration : rotationDownDuration);
            }
        }
        /* конец изменения длины вызжающего кубика(чтобы устранить щель) */
    }
    /* конец блока анимации */
}


