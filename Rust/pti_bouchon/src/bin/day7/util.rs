pub struct AoCFile {
    pub name: String,
    pub size: usize,
}

pub struct AoCDirectory {
    pub name: String,
    pub files: Vec<AoCFile>,
    pub childrens_directory: Vec<String>,
}
