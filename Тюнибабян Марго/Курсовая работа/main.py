# Для разбора аргументов CLI (командной строки).
import argparse
# Работа с файловой системой.
import os
# Системные вызовы.
import sys
# Работа с CSV.
import csv
# Работа с датой и временем системы.
from datetime import datetime
# Библиотека для рисования.
from PIL import Image, ImageDraw, ImageFont


def profile_cut(lengths_with_tolerance, profile_length, lengths, tolerance):
    """
    Задача решается методом динамического программирования на основе алгоритмов П. Гилмора и Р. Гомори.
    За пример взята задача о "ранце" или "рюкзаке", где
    в роли рюкзака выступает длина профиля,
    в роли веса вещей выступают длины заготовок с допуском распила,
    в роли стоимостей вещей выступают реальный длины заготовок.
    :param lengths_with_tolerance: список длин заготовок с допуском.
    :param profile_length: длина профиля.
    :param lengths: список запрашиваемых длин заготовок.
    :param tolerance: допуск распила.
    :return:
    """
    # print("lengths_with_tolerance=", lengths_with_tolerance, "profile_length=", profile_length, "lengths=", lengths)

    bar = {0: 0}  # Хэш: самый оптимальный вариант распила профиля (с наименьшим остатком) - {длина с допуском:длина}
    solution = {0: []}
    # Цикл по всем заготовкам.
    for i in range(0, len(lengths_with_tolerance)):
        current = lengths[i]
        current_w = lengths_with_tolerance[i]
        if len(bar) == 1:
            # Уберём из первой заготовки допуск, подразумевая, что все остальные будут с допуском.
            # В обычной жизни можно предположить, что для последней "влезающей" в профиль заготовки не нужно считать допуск,
            # но в данной ситуации удобнее забрать допуск у первой заготовки.
            current_w -= tolerance

        bar_pre = bar.copy()  # Сохраним состояние таблицы профиля.
        # print(lengths[i], "/", lengths_with_tolerance[i], ":", bar)

        # Цикл по всем полученным частичным длинам с допуском.
        for x in bar_pre:
            sum_lehgths = (x + current_w)
            if sum_lehgths <= profile_length:
                if (not (x + current_w) in bar.keys()) or (
                        bar[x + current_w] < bar_pre[x] + current):
                    bar[x + current_w] = bar_pre[x] + current
                    solution[x + current_w] = solution[x] + [i]
        # print("    -->", bar)

    result_length = max(bar.values())
    idx = max(bar, key=bar.get)
    result = solution.get(idx)
    # По умолчанию остаток равен длине профиля.
    remain = profile_length
    if len(result) != 0:
        # Если у нас есть варианты распила - высчитаем остаток, вычитая из длины профиля длину всех заготовок,
        # а так же ширину допуска, умноженную на кол-во распилов на профиле.
        remain = profile_length - result_length - tolerance * (len(result) - 1)
        if len(result) == 1 and profile_length != result_length:
            # для случая, когда у нас 1 распил на профиле (длина result = 1)
            remain = profile_length - result_length - tolerance
    # print(result, ":", result_length)

    return (result, result_length, remain)


if __name__ == '__main__':
    # Инициализируем парсер аргументов.
    parser = argparse.ArgumentParser(
        description='Создаёт карты оптимального распила профилей. Сохраняет графические файлы и CSV в соответсвующие папки.')
    parser.add_argument("--tolerance", "-t", help="указать технический допуск (целое число)")
    parser.add_argument("--profiles", "-p", help="указать путь к файлу с данными профилей")
    parser.add_argument("--order", "-o", help="указать путь к файлу с данными заготовок (файл заказа)")
    parser.add_argument("-V", "--version", help="показать версию программы", action="store_true")
    args = parser.parse_args()

    # Существующие профили (длины, скажем, в мм)
    profiles = []
    # Длины требуемых заготовок (в мм)
    order = []
    # Допуск (ширина распила, мм).
    tolerance = 0

    # Показать версию.
    if args.version:
        print("Версия 0.1")
        sys.exit()

    # Установить допуск.
    if args.tolerance:
        try:
            tolerance = int(args.tolerance)
        except Exception as e:
            print(f'неверный параметр -t: {e}')
            sys.exit()
        if tolerance == 0:
            print(f'обратите внимание - не указан допуск')

    # Установить данные о профилях.
    if args.profiles:
        profiles_filepath = str(args.profiles).strip()
        if profiles_filepath == '':
            print(f'не указан путь к файлу данных о профилях')
            sys.exit()
        try:
            # Откроем файл с профилями и разберём его на список.
            with open(profiles_filepath, newline='') as csvfile:
                reader = csv.DictReader(csvfile)
                for row in reader:
                    profiles += [int(row['length'])] * int(row['count'])
        except Exception as e:
            print(f'неверный параметр -p: {e}')
            sys.exit()
        if len(profiles) == 0:
            print('не найдено данных о профилях')
            sys.exit()
    else:
        print(f'не указан путь к файлу данных о профилях')
        sys.exit()

    # Установить данные о заказе (заготовках).
    if args.order:
        order_filepath = str(args.order).strip()
        if order_filepath == '':
            print(f'не указан путь к файлу данных о заготовках')
            sys.exit()
        try:
            # Откроем файл с заготовками и разберём его на список.
            with open(order_filepath, newline='') as csvfile:
                reader = csv.DictReader(csvfile)
                for row in reader:
                    order += [int(row['length'])] * int(row['count'])
        except Exception as e:
            print(f'неверный параметр -o: {e}')
            sys.exit()
        if len(order) == 0:
            print('не найдено данных о заготовках')
            sys.exit()
    else:
        print(f'не указан путь к файлу данных о заготовках')
        sys.exit()

    # Заготовка для карт распиловок по каждому профилю.
    maps = list()
    # Заготовка для остатков после распиловок по каждому профилю.
    remains = list()

    # Сортируем профили по убыванию: от большего к меньшему.
    profiles = sorted(profiles, reverse=True)
    # Сортируем заготовки по убыванию: от большего к меньшему.
    order = sorted(order, reverse=True)

    # Определим минимальную длину профиля.
    p_min = min(profiles)

    # Печать исходных данных.
    print(f'Имеются профили: {profiles}, в мм.')
    print(f'Длина наименьшего профиля: {p_min}, в мм.')
    print(f'Поступил заказ на заготовки: {order}, в мм.')
    print(f'Ширина распила (допуск): {tolerance} мм.')

    # Метка времени выполнения операции, может понадобиться для создания папок вывода.
    now = datetime.utcnow()
    # Подготовим паку для выгрузки результатов в CSV.
    output_path_csv = os.path.join('output', f'{now.timestamp()}', 'csv')
    if not os.path.exists(output_path_csv):
        try:
            os.makedirs(output_path_csv)
        except Exception as e:
            print(f'не удалось создать папку для результата работы: {e}')
    # Подготовим паку для выгрузки результатов в IMG.
    output_path_img = os.path.join('output', f'{now.timestamp()}', 'img')
    if not os.path.exists(output_path_img):
        try:
            os.makedirs(output_path_img)
        except Exception as e:
            print(f'не удалось создать папку для результата работы: {e}')

    # Счётчик профилей, чтоб не перепутать карты распила для профилей с одинаковой длиной.
    profiles_counter = 1
    # Перебираем по одному профилю.
    for profile in profiles:
        # Зададим список заготовок с прибавленным допуском.
        order_w = [x + tolerance for x in order]
        # Поиск оптимального решения.
        complect = profile_cut(lengths_with_tolerance=order_w, profile_length=profile, lengths=order,
                               tolerance=tolerance)
        # Заготовка карты распила для текущего профиля.
        profile_map = {
            profiles_counter: {
                profile: list(),
            }
        }
        # Остаток профиля после распила.
        profile_remain = {
            profiles_counter: {
                profile: complect[2],
            }
        }
        # Удалим из списка "обработанные" заготовки, чтоб второй раз не примерять их к профилю
        # ...сначала приведём список в словарь, чтоб не ошибится с индексом удаляемого элемента.
        order_d = {i: order[i] for i in range(0, len(order))}
        # Перебирая индексы полученных "удачных" заготовок для профиля.
        for cmpl in complect[0]:
            # возьмём оптимальную карту распила для данного профиля, сразу удаляя из временного словаря заготовок.
            profile_map[profiles_counter][profile].append(order_d.pop(cmpl))

        # Вернём значения заказов из временного словаря обратно в список.
        order = list(order_d.values())
        # Сортирнём список заготовок по убыванию.
        order = sorted(order, reverse=True)

        # Соберём остаток после распила профиля в результат ответов.
        remains.append(profile_remain)

        # Заберём оптимальную карту распила профиля в результат ответов.
        maps.append(profile_map)

        # увеличим счетчик профилей.
        profiles_counter += 1

    # Перебирая карты распиловки, напечатаем примитивный план.
    # Соберём данные для выгрузки в CSV.
    result_maps = []
    for number_map in maps:
        for _map in list(number_map.values()):
            for profile_length in _map.keys():
                print(
                    f'Для профиля длиной {profile_length} оптимальный набор длин заготовок: {_map.get(profile_length)}')
                # Длины заготовок.
                bars = _map.get(profile_length)
                # Первый элемент строки - длина профиля.
                result_map = [profile_length]
                if len(bars) > 1:
                    # Вставим допуск между длинами заготовок, если заготовка не одна.
                    bars_w = list()
                    # счетчик длин заготовок, чтоб не пропустить последнюю и не прибавить лишний допуск.
                    counter_bar = len(bars) - 1
                    for bar in bars:
                        if counter_bar != 0:
                            bars_w.append(bar)
                            bars_w.append(tolerance)
                        else:
                            bars_w.append(bar)
                        counter_bar -= 1
                    result_map += bars_w
                else:
                    result_map += bars

                result_maps.append(result_map)

    # Выгрузим текстовый файл карт распила.
    csv_output = os.path.join(output_path_csv, 'output.csv')
    with open(csv_output, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile, delimiter=',')
        for _map in result_maps:
            writer.writerow(_map)

    # Выгрузим графические файлы карт распила.
    maps_counter = 1
    # путь до файла шрифта, иначе не установить размер шрифта.
    font_path = 'assets/fonts/InputSans-Regular.ttf'
    font = ImageFont.truetype(font_path, 24)
    for _map in result_maps:
        if len(_map) < 2:
            # Пропустим профили без заготовок.
            continue
        img_w = 1754
        img_h = 1240

        # за поля примем 150px
        margin = 150
        # Полезная область листа.
        img_w_useful = img_w - margin * 2
        img_h_useful = img_h - margin * 2

        # Масштаб.
        scale = 1.0

        # Определим соотношение длины профиля к размеру листа, смасштабируем, если это потребуется.
        if img_w_useful < _map[0]:
            scale = _map[0] / img_w_useful

        # Пустой белый фон, альбомный лист А4 с разрешением DPI = 150.
        im = Image.new('RGB', (img_w, img_h), (255, 255, 255))
        draw = ImageDraw.Draw(im)
        # Рисуем отрезок профиля.
        x1 = margin
        y1 = int(img_h_useful / 2)
        x2 = int(_map[0] / scale) + margin
        y2 = int(img_h_useful / 2)
        draw.line((x1, y1, x2, y2), fill='black', width=4)
        # Обозначим начало и конец профиля цифрами.
        draw.text((x1 - 50, y1 - 50), '0', fill=(0, 0, 0), font=font)
        draw.text((x2, y2 - 50), f'{_map[0]}', fill=(0, 0, 0), font=font)
        # Обозначим допуск.
        draw.text((170, 170), f'Допуск распила = {tolerance}', fill=(0, 0, 0), font=font)

        # Рисуем отрезки распилов.
        expl = margin  # тут будем хранить длину отрезков, по которым сделали засечки,
        # оно же будет выступать координатой X для рисования засечки на отрезке.
        for point in _map[1:]:
            expl += int(point / scale)
            x1 = expl
            y1 = int(img_h_useful / 2) - 10
            x2 = x1
            y2 = int(img_h_useful / 2) + 10
            draw.line((x1, y1, x2, y2), fill='black', width=1)
            if point != tolerance:
                # Напишем длины отрезков, только без допусков.
                text_x = int(x1 - point / scale / 2)
                text_y = y2
                draw.text((text_x, text_y), f'{point}', fill=(0, 0, 0), font=font)

        # Определим, нужно ли списать остаток.
        offcut = _map[0] - sum(_map[1:])
        if offcut < p_min:
            draw.text((170, img_h-170), f'Остаток профиля {offcut} списать', fill=(0, 0, 0), font=font)
        else:
            draw.text((170, img_h-170), f'Остаток профиля {offcut} отправить в дальнейшую обработку', fill=(0, 0, 0), font=font)


        img_path = os.path.join(output_path_img, f'{_map[0]}_{maps_counter}.jpg')
        im.save(img_path, quality=95)
        maps_counter += 1

    # Перебирая остатки распиловки, напечатаем их для информации.
    for number_remain in remains:
        for _remain in list(number_remain.values()):
            for profile_length in _remain.keys():
                # Списать профиль, если его остаток меньше наименьшего профиля (по условию задачи).
                if _remain.get(profile_length) < p_min:
                    print(f'Для профиля длиной {profile_length} остаток: {_remain.get(profile_length)}. Списан.')
                else:
                    print(
                        f'Для профиля длиной {profile_length} остаток: {_remain.get(profile_length)}. Подходит для дальнейшей обработки.')

    # Напечатаем длины заготовок, на которые не хватило профилей, если они остались.
    if len(order) > 0:
        print(f'Для заготовок {order} не достаточно профилей.')
