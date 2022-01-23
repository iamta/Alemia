import os
import glob
import shutil
import re
import zipfile
import subprocess


def create_dir(path):
    if not (os.path.isdir(path)):
        os.mkdir(path)


def preprocess_datas(src_dir, dest_dir):
    newfiles = []
    dest_fields = dest_dir.split("/")

    for filename in glob.iglob(src_dir + "**/*.*", recursive=True):
        fields = filename.split("/")

        my_dir = ""
        for i in range(len(fields)):
            if fields[i] == dest_fields[3]:
                my_dir = fields[i + 1]

        if all(x not in my_dir for x in newfiles):
            newfiles.append(my_dir)

        create_dir(dest_dir + "/" + my_dir)
        create_dir(dest_dir + "/" + my_dir + "/text")
        create_dir(dest_dir + "/" + my_dir + "/headers")
        create_dir(dest_dir + "/" + my_dir + "/sources")
        create_dir(dest_dir + "/" + my_dir + "/rest")

        if (filename.endswith(".txt")):
            shutil.copy2(filename, dest_dir + my_dir + "/text/" + fields[-1])
        elif (filename.endswith(".h")):
            shutil.copy2(filename,
                         dest_dir + my_dir + "/headers/" + fields[-1])
        elif (filename.endswith(".cpp")):
            shutil.copy2(filename,
                         dest_dir + my_dir + "/sources/" + fields[-1])
        elif ("Debug" in filename or "DEBUG" in filename or "/." in filename) == False:
            print(filename)
            shutil.copy2(filename, dest_dir + my_dir + "/rest/" + fields[-1])

    return newfiles


def get_regex_counts(filename, regex_pattern):
    counts = 0
    for _, line in enumerate(open(filename, "r", encoding="ISO-8859-1")):
        for _ in re.finditer(regex_pattern, line):
            counts += 1

    return counts


def create_csv(trainDir, outfilename, students):
    output = open(outfilename, "w")

    output.write(
        "nr_crt,label,nr_clase,nr_errors,nr_inheritance,nr_virtual,nr_static,")
    output.write(
        "nr_global,nr_public,nr_private,nr_protected,nr_define,nr_template,")
    output.write("nr_stl,nr_namespace,nr_enum,nr_struct,nr_cpp,")
    output.write("nr_comments,nr_function,headers_size,sources_size,\n")

    nrCrt = 0
    for std in students:
        local_dir = trainDir + std

        headers = [
            h for h in os.listdir(local_dir + "/headers/")
            if os.path.isfile(os.path.join(local_dir + "/headers/", h))
        ]
        sources = [
            s for s in os.listdir(local_dir + "/sources/")
            if os.path.isfile(os.path.join(local_dir + "/sources/", s))
        ]

        class_number = len(headers)
        sources_number = len(sources)

        if not (os.path.isfile(trainDir + std + "/codying_style.txt")):
            command = ["cpplint", "--recursive", local_dir + "/sources/"]
            output_filename = trainDir + std + "/codying_style.txt"
            with open(output_filename, "w") as output_file:
                proc = subprocess.Popen(command,
                                        stdout=output_file,
                                        stderr=output_file)
                proc.wait()

        with open(trainDir + std + "/codying_style.txt", "r") as f:
            lines = f.read().splitlines()
            last_line = lines[-1]
        codying_errors = last_line.split(" ")[-1]

        inheritance_pattern = re.compile(r"([A-Z])\w+ : ([a-z]\w+)")
        virtual_pattern = re.compile(r"virtual ([a-z]\w+)")
        static_pattern = re.compile(r"\W*(static)\W*")
        global_pattern = re.compile(r"\W*(global)\W*")
        public_pattern = re.compile(r"\W*(public)\W*")
        private_pattern = re.compile(r"\W*(private)\W*")
        protected_pattern = re.compile(r"\W*(protected)\W*")
        define_pattern = re.compile(r"^#define*")
        template_pattern = re.compile(r"\W*(template)\W*")
        stl_pattern = re.compile(r"\W*(std)\W*")
        namespace_pattern = re.compile(r"\W*(namespace)\W*")
        comments_pattern = re.compile(r"\W*(/\*)|(//)\W*")
        enum_pattern = re.compile(r"\W*(enum)\W*")
        struct_pattern = re.compile(r"W*(stuct)\W*")
        function_pattern = re.compile(r"\W*(\(\))\W*")

        inheritance_count = 0
        virtual_count = 0
        static_count = 0
        global_count = 0
        public_count = 0
        private_count = 0
        protected = 0
        define_count = 0

        template_count = 0
        stl_count = 0
        namespace_count = 0
        comments_count = 0
        enum_count = 0
        struct_count = 0
        function_count = 0

        sources_size = 0
        headers_size = 0
        for source in sources:
            sources_size += os.path.getsize(local_dir + "/sources/" + source)

        for header in headers:
            inheritance_count += get_regex_counts(
                local_dir + "/headers/" + header, inheritance_pattern)
            virtual_count += get_regex_counts(local_dir + "/headers/" + header,
                                              virtual_pattern)
            static_count += get_regex_counts(local_dir + "/headers/" + header,
                                             static_pattern)
            global_count += get_regex_counts(local_dir + "/headers/" + header,
                                             global_pattern)
            public_count += get_regex_counts(local_dir + "/headers/" + header,
                                             public_pattern)
            private_count += get_regex_counts(local_dir + "/headers/" + header,
                                              private_pattern)
            protected += get_regex_counts(local_dir + "/headers/" + header,
                                          protected_pattern)
            define_count += get_regex_counts(local_dir + "/headers/" + header,
                                             define_pattern)
            template_count += get_regex_counts(
                local_dir + "/headers/" + header, template_pattern)
            stl_count += get_regex_counts(local_dir + "/headers/" + header,
                                          stl_pattern)
            namespace_count += get_regex_counts(
                local_dir + "/headers/" + header, namespace_pattern)
            comments_count += get_regex_counts(
                local_dir + "/headers/" + header, comments_pattern)
            enum_count += get_regex_counts(local_dir + "/headers/" + header,
                                           enum_pattern)
            struct_count += get_regex_counts(local_dir + "/headers/" + header,
                                             struct_pattern)

            function_count += get_regex_counts(
                local_dir + "/headers/" + header, function_pattern)
            headers_size += os.path.getsize(local_dir + "/headers/" + header)

        to_Write = []
        to_Write.append(nrCrt)
        to_Write.append(std)
        to_Write.append(class_number)
        to_Write.append(codying_errors)
        to_Write.append(inheritance_count)
        to_Write.append(virtual_count)
        to_Write.append(static_count)
        to_Write.append(global_count)
        to_Write.append(public_count)
        to_Write.append(private_count)
        to_Write.append(protected)
        to_Write.append(define_count)
        to_Write.append(template_count)
        to_Write.append(stl_count)
        to_Write.append(namespace_count)
        to_Write.append(enum_count)
        to_Write.append(struct_count)
        to_Write.append(sources_number)
        to_Write.append(comments_count)
        to_Write.append(function_count)
        to_Write.append(headers_size)
        to_Write.append(sources_size)

        for w in to_Write:
            output.write(str(w) + ",")
        output.write("\n")

        nrCrt += 1

    output.close()


def extract_zip(zipPath, destPath, scope):
    with zipfile.ZipFile(zipPath, "r") as zip_ref:
        if not (os.path.isdir(destPath + scope)):
            zip_ref.extractall(destPath)
        else:
            print("[INFO] " + scope + " dataset exists")


def merge_csv(src, dest):
    file1 = open(dest, "r+")
    file2 = open(src, "r")

    Lines = file1.readlines()
    last_line = Lines[-1]
    last_index = last_line.split(",")[0]
    Lines2 = file2.readlines()

    for line in Lines2[1:]:
        fields = line.split(",")
        nr_crt = int(fields[0]) + int(last_index) + 1
        file1.write(str(nr_crt) + ",")
        for f in fields[1:len(fields) - 1]:
            file1.write(f + ",")
        file1.write("\n")

    return Lines2[1:]


def init_setup():
    trainDir = "../data/preprocessed/train/"
    testDir = "../data/preprocessed/test/"

    create_dir("../data/preprocessed/")
    create_dir(trainDir)
    create_dir(testDir)

    preprocess_datas("../data/raw/train/", trainDir)
    preprocess_datas("../data/raw/test/", testDir)

    students = [
        d for d in os.listdir(trainDir)
        if os.path.isdir(os.path.join(trainDir, d))
    ]
    create_csv(trainDir, "../data/features.csv", students)

    students = [
        d for d in os.listdir(testDir)
        if os.path.isdir(os.path.join(testDir, d))
    ]
    create_csv(testDir, "../data/test_features.csv", students)

    return students


def retrain_data_one(path_to_new_label):
    trainDir = "../data/preprocessed/train/"

    newLabel = preprocess_datas(path_to_new_label, trainDir)
    allLabels = [
        d for d in os.listdir(trainDir)
        if os.path.isdir(os.path.join(trainDir, d))
    ]
    newLabels = []
    for label in allLabels:
        if (label == newLabel[0]):
            newLabels.append(label)

    create_csv(trainDir, "../data/featuresRetrained.csv", newLabels)
    new_data = merge_csv("../data/featuresRetrained.csv",
                         "../data/features.csv")
    os.remove("../data/featuresRetrained.csv")

    new_data = (new_data[0].split(","))[1:-1]

    return new_data


def add_new_line_csv(csv_file, data):
    file1 = open(csv_file, "r+")

    Lines = file1.readlines()
    last_line = Lines[-1]
    last_index = last_line.split(",")[0]

    for i in range(len(data)):
        if i == 0:
            nr_crt = int(data[i]) + int(last_index) + 1
            file1.write(str(nr_crt) + ",")
        file1.write(data[i] + ",")

    file1.write("\n")